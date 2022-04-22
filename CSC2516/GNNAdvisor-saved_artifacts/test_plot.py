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


rc_init()
bar_width, annotation_fontsize = 1, 18
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

def annotate_list(list, x, annotation_fontsize, initial_side=True,
                  force_annotate=lambda k: False):
    vlist = [kv[1][0] if isinstance(kv[1], type([])) else kv[1] for kv in list]
    side, prev_side = initial_side, initial_side
    prev_pct = None
    for i in range(len(list)):
        middle_pos = vlist[i] / 2 + np.sum(vlist[i+1:])
        bar_length = vlist[i]
        curr_pct = vlist[i] / plt.ylim()[1]

        if vlist[i] / plt.ylim()[1] < 0.05:
            if not force_annotate(list[i][0]):
                continue
        if prev_pct is not None and (prev_pct < 0.1 or curr_pct < 0.05):
            side = not prev_side

        plt.annotate('%.0f%%' % (vlist[i] * 100.0 / sum(vlist)),
                     xy    =(x+0.53 * (1 if side is True else -1), middle_pos), 
                     xytext=(x+0.68 * (1 if side is True else -1), middle_pos), 
                     fontsize=annotation_fontsize,
                     ha='left' if side is True else 'right', 
                     va='center', 
                     bbox=dict(boxstyle='square', facecolor='white', linewidth=3),
                     arrowprops=dict(arrowstyle="-[, widthB=%f, lengthB=0.3" % 
                                                    (0.54 / plt.ylim()[1] * annotation_fontsize * bar_length),
                                     linewidth=2)
                     )
        prev_side = side
        prev_pct = curr_pct


def test_gcn_and_gin():
    gin_gpu_kernel_profile, _ = \
            parse_profile('citeseer-gin.csv',
                          {lambda kernel_name: "sgemm" in kernel_name :
                           lambda kernel_name: "Transform",
                           lambda kernel_name: "spmm"  in kernel_name :
                           lambda kernel_name: "Aggregate"}
                           )
    gcn_gpu_kernel_profile, _ = \
            parse_profile('citeseer-gcn.csv',
                          {lambda kernel_name: "sgemm" in kernel_name :
                           lambda kernel_name: "Transform",
                           lambda kernel_name: "spmm"  in kernel_name :
                           lambda kernel_name: "Aggregate",
                           lambda kernel_name: "NLL"  in kernel_name :
                           lambda kernel_name: "Log-Softmax"}
                          )

    xlabel = "\nGPU Runtime Profile"
    ylabel = r"Runtime ($\mathrm{ms}$)"
    fig_name = "GNN_nvprof_Results.png"

    plt.figure(figsize=(10, 6))

    gcn_handle = plot_list(gcn_gpu_kernel_profile, 0)
    gin_handle = plot_list(gin_gpu_kernel_profile, 3)
    annotate_list(gcn_gpu_kernel_profile, 0, annotation_fontsize, False)
    annotate_list(gin_gpu_kernel_profile, 3, annotation_fontsize, True)

    plt.xlim([-2*bar_width, 3 + 2*bar_width])
    plt.xticks([0, 3], ['GCN', 'GIN'])
    plt.ylabel(ylabel)

    # Grid & Legend
    plt.grid(linestyle='-.', linewidth=1, axis='y')

    plt.tight_layout()
    plt.legend(handles=gcn_handle)
    plt.savefig(fig_name)



def test_gin_vs_gin_v2():
    gin_gpu_kernel_profile, _ = \
            parse_profile('citeseer-gin.csv',
                          {lambda kernel_name: "sgemm" in kernel_name :
                           lambda kernel_name: "Transform",
                           lambda kernel_name: "spmm"  in kernel_name :
                           lambda kernel_name: "Aggregate"}
                           )
    gin_v2_gpu_kernel_profile, _ = \
            parse_profile('citeseer-gin_v2.csv',
                          {lambda kernel_name: "sgemm" in kernel_name :
                           lambda kernel_name: "Transform",
                           lambda kernel_name: "spmm"  in kernel_name :
                           lambda kernel_name: "Aggregate"}
                          )

    xlabel = "\nGPU Runtime Profile"
    ylabel = r"Runtime ($\mathrm{ms}$)"
    fig_name = "GIN_vs_EarlyMLP.png"

    plt.figure(figsize=(10, 6))

    gin_handle = plot_list(gin_gpu_kernel_profile, 0)
    gin_v2_handle = plot_list(gin_v2_gpu_kernel_profile, 3)
    annotate_list(gin_gpu_kernel_profile, 0, annotation_fontsize, False)
    annotate_list(gin_v2_gpu_kernel_profile, 3, annotation_fontsize, True,
                  force_annotate=lambda k: True if k == "Aggregate" else False)

    plt.xlim([-2*bar_width, 3 + 2*bar_width])
    plt.xticks([0, 3], ['Baseline', 'EarlyMLP'])
    plt.ylabel(ylabel)

    # Grid & Legend
    plt.grid(linestyle='-.', linewidth=1, axis='y')

    plt.tight_layout()
    plt.legend(handles=gin_handle)
    plt.savefig(fig_name)


def save_legend(handles, title, ncol=5, alphas=None):
    lgd_fig = plt.figure()
    plt.axis('off')
    lgd = plt.legend(handles=handles, loc='center', ncol=int(ncol))

    if alphas is not None:
        for i, text in enumerate(lgd.get_texts()):
            text.set_alpha(alphas[i])

    lgd_fig.canvas.draw()
    plt.savefig(title, 
                bbox_inches=lgd.get_window_extent().transformed(lgd_fig.dpi_scale_trans.inverted()))
    plt.close()


from collections import OrderedDict

def test_perf():
    fig = plt.figure(figsize=(10, 6))
    buffer = []
    num_measure_records = 0

    latencies = OrderedDict()

    perf_results = {}

    for backend in ['DGL', 'GNNAdvisor', 'EarlyMLP']:
        with open(f'gin-{backend}.csv') as fin:
            csv_fin = csv.DictReader(fin)
            for i, row in enumerate(csv_fin):
                if row['dataset'] not in perf_results:
                    perf_results[row['dataset']] = OrderedDict()
                perf_results[row['dataset']][backend] = row['Avg.Epoch (ms)']

    print(perf_results)

    x = 0

    legend_handles = []

    datasets = ['CiteSeer', 'CORA', 'Pubmed', 'PPI']
    datasets_lowered = [d.lower() for d in datasets]

    bar_gap = 1.5

    for i, dataset in enumerate(datasets_lowered):
        print(perf_results[dataset])
        for j, result in enumerate(perf_results[dataset].items()):
            bar_legend = plt.bar(x, float(result[1]),
                                 bar_width, edgecolor='black', linewidth=3,
                                 color=cycle[j], label=result[0])
            if i == 0:
                legend_handles.append(bar_legend)
            x += bar_width
        x += bar_gap
    for j, result in enumerate(perf_results['citeseer'].items()):
        bar_legend = plt.bar(x, np.average([float(perf_results[d][result[0]]) for d in datasets_lowered]),
                             bar_width, edgecolor='black', linewidth=3,
                             color=cycle[j], label=result[0])
        x += bar_width

    x = 0

    for i, dataset in enumerate(datasets_lowered):
        for j, result in enumerate(perf_results[dataset].items()):
            plt.text(x, 0.9 * plt.ylim()[1],
                     r'$%.3f\times$' % (float(result[1]) / float(perf_results[dataset]['DGL'])),
                     ha='center', backgroundcolor='white',
                     rotation=45, fontsize=20,
                     bbox=dict(boxstyle="round", fc='white', alpha=0.9, pad=0.2))
            x += bar_width
        x += bar_gap

    dgl_baseline_avg = np.average([float(perf_results[d]['DGL']) for d in datasets_lowered])

    for j, result in enumerate(perf_results['citeseer'].items()):
        plt.text(x, 0.9 * plt.ylim()[1],
                 r'$%.3f\times$' % (np.average([float(perf_results[d][result[0]]) for d in datasets_lowered]) / dgl_baseline_avg),
                 ha='center', backgroundcolor='white',
                 rotation=45, fontsize=20,
                 bbox=dict(boxstyle="round", fc='white', alpha=0.9, pad=0.2))
        x += bar_width

    datasets.append('Average')

    xticks = ((1, 1 + bar_gap + 3, 1 + 2 * (bar_gap + 3), 1 + 3 * (bar_gap + 3),
               1 + 4 * (bar_gap + 3)), datasets)
    plt.xticks(*xticks)
    plt.ylabel(r"Latency$/$Iteration ($\mathrm{ms}$)")

    plt.grid(linestyle='-.', linewidth=1)

    plt.tight_layout()
    plt.savefig("EarlyMLP.png")

    save_legend(legend_handles, 'EarlyMLP_legend.png')
