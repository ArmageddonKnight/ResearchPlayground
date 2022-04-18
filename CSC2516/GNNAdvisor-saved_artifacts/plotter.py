import csv
import matplotlib
import matplotlib.pyplot as plt
import numpy as np


def _reduce(sorted_list, top_k):
    if top_k is None:
        return sorted_list
    sorted_list_reduce = []
    for i in range(top_k):
        sorted_list_reduce.append(sorted_list[i])
    sorted_list_reduce.append(('Others', sum([iter[1] for iter in sorted_list[top_k:]])))
    return sorted_list_reduce


def analyze(nvprofile_path, transform_lambda_dict={}):
    expected_row_len = 8

    gpu_kernel_info, cuda_api_info = {}, {}

    def _truncate(tag):
        return tag[:30] + '..' if len(tag) > 30 else tag

    with open(nvprofile_path, 'r') as csvfile:
        reader = csv.reader(csvfile)
        for row in reader:
            if len(row) == 0:
                continue # ignore empty lines

            if "GPU activities" in row[0]:
                gpu_kernel_name = row[expected_row_len - 1]

                for key, transform in transform_lambda_dict.items():
                    if key(gpu_kernel_name):
                        gpu_kernel_name = transform(gpu_kernel_name)

                if gpu_kernel_name in gpu_kernel_info:
                    gpu_kernel_info[gpu_kernel_name] += float(row[2])
                else:
                    gpu_kernel_info[gpu_kernel_name]  = float(row[2])
            if "API calls" in row[0]:
                cuda_api_name = row[expected_row_len - 1].split("cuda")[-1]
                cuda_api_name = "Launch" if "Launch" in cuda_api_name else cuda_api_name
                cuda_api_name = "Synchronize" if "Synchronize" in cuda_api_name else cuda_api_name
                cuda_api_info[cuda_api_name] = float(row[2])

    return _reduce(sorted(gpu_kernel_info.items(), key=lambda kv : kv[1], reverse=True), len(transform_lambda_dict)), \
           _reduce(sorted(cuda_api_info  .items(), key=lambda kv : kv[1], reverse=True), len(transform_lambda_dict))


def parse_profile(nvprofile_path, transform_lambda_dict):
    gpu_kernel_profile, cuda_api_profile = \
            analyze(
                nvprofile_path=nvprofile_path, 
                transform_lambda_dict=transform_lambda_dict
            )
    print(gpu_kernel_profile, cuda_api_profile)
    return gpu_kernel_profile, cuda_api_profile


def rc_init(dpi=100, fontsize=24):
    plt.rc('figure', dpi=dpi)
    plt.rc('axes', axisbelow=True)
    plt.rc('mathtext', fontset='cm')
    plt.rc('mathtext', rm='Times New Roman')
    plt.rc('font', family='Times New Roman', size=fontsize)


if __name__ == '__main__':
    gin_gpu_kernel_profile, _ = \
            parse_profile('citeseer-gin-2357.csv',
                          {lambda kernel_name: "sgemm" in kernel_name :
                           lambda kernel_name: "Transform",
                           lambda kernel_name: "spmm"  in kernel_name :
                           lambda kernel_name: "Aggregate"}
                           )
    gcn_gpu_kernel_profile, _ = \
            parse_profile('citeseer-gcn-2319.csv',
                          {lambda kernel_name: "sgemm" in kernel_name :
                           lambda kernel_name: "Transform",
                           lambda kernel_name: "spmm"  in kernel_name :
                           lambda kernel_name: "Aggregate",
                           lambda kernel_name: "NLL"  in kernel_name :
                           lambda kernel_name: "Log-Softmax"}
                          )

    rc_init()

    xlabel = "\nGPU Runtime Profile"
    ylabel = r"Runtime ($\mathrm{ms}$)"
    fig_name = "GNN_nvprof_Results.png"

    bar_width, annotation_fontsize = 1, 18
    plt.figure(figsize=(10, 6))

    cycle = plt.rcParams['axes.prop_cycle'].by_key()['color']

    def plot_list(list, x):
        legend_handles = []
        klist = [kv[0] for kv in list]
        vlist = [kv[1][0] if isinstance(kv[1], type([])) else kv[1] for kv in list]
        for i in range(len(list)):
            legend_handles.append(
                    plt.bar(x=x, height=vlist[i], bottom=np.sum(vlist[i+1:]),
                        width=bar_width, edgecolor='black', linewidth=3,
                        color=cycle[0] if klist[i] == "Transform" else
                              cycle[1] if klist[i] == "Aggregate" else
                              cycle[2] if klist[i] == "Log-Softmax"
                              else 'white',
                        label=klist[i]))
        return legend_handles

    def annotate_list(list, x, annotation_fontsize, initial_side=True):
        vlist = [kv[1][0] if isinstance(kv[1], type([])) else kv[1] for kv in list]
        side, prev_side = initial_side, initial_side
        prev_percentage = None
        for i in range(len(list)):
            middle_pos = vlist[i] / 2 + np.sum(vlist[i+1:])
            bar_length = vlist[i]
            if vlist[i] / plt.ylim()[1] < 0.05:
                continue
            if prev_percentage is not None and prev_percentage < 0.1:
                side = not prev_side

            plt.annotate('%.0f%%' % (vlist[i] * 100.0 / sum(vlist)),
                    xy    =(x+0.53 * (1 if side is True else -1), middle_pos), 
                    xytext=(x+0.68  * (1 if side is True else -1), middle_pos), 
                    fontsize=annotation_fontsize,
                    ha='left' if side is True else 'right', 
                    va='center', 
                    bbox=dict(boxstyle='square', facecolor='white', linewidth=3),
                    arrowprops=dict(arrowstyle="-[, widthB=%f, lengthB=0.3" % 
                        (0.54 / plt.ylim()[1] * annotation_fontsize * bar_length),
                    linewidth=2))
            prev_side = side
            prev_percentage = vlist[i] / plt.ylim()[1]

    gcn_handle = plot_list(gcn_gpu_kernel_profile, 0)
    gin_handle = plot_list(gin_gpu_kernel_profile, 3)
    annotate_list(gcn_gpu_kernel_profile, 0, annotation_fontsize, False)
    annotate_list(gin_gpu_kernel_profile, 3, annotation_fontsize, True)

    plt.xlim([-2*bar_width, 3 + 2*bar_width])
    plt.xticks([0, 3], ['GCN', 'GIN'])
    # plt.xlabel(xlabel)
    plt.ylabel(ylabel)

    # Grid & Legend
    plt.grid(linestyle='-.', linewidth=1, axis='y')

    plt.tight_layout()
    plt.legend(handles=gcn_handle)
    plt.savefig(fig_name)
