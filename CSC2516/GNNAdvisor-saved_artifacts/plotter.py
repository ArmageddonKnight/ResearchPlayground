import csv
import matplotlib


def _reduce(sorted_list, top_k):
    if top_k is None:
        return sorted_list
    sorted_list_reduce = []
    for i in range(top_k):
        sorted_list_reduce.append(sorted_list[i])
    sorted_list_reduce.append(('Others', sum([iter[1] for iter in sorted_list[top_k:]])))
    return sorted_list_reduce


def analyze(nvprofile_path, top_k=[None, None], transform_lambda_dict={}):
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

    return _reduce(sorted(gpu_kernel_info.items(), key=lambda kv : kv[1], reverse=True), top_k[0]), \
           _reduce(sorted(cuda_api_info  .items(), key=lambda kv : kv[1], reverse=True), top_k[1])


transform_lambda_dict = { 
            lambda kernel_name: "sgemm" in kernel_name :
            lambda kernel_name: "Transform",
            lambda kernel_name: "spmm"  in kernel_name :
            lambda kernel_name: "Aggregate"
        }

def parse_profile(nvprofile_path):
    gpu_kernel_profile, cuda_api_profile = \
            analyze(
                nvprofile_path=nvprofile_path, 
                top_k=[3, 2],
                transform_lambda_dict=transform_lambda_dict
            )
    print(gpu_kernel_profile, cuda_api_profile)
    return gpu_kernel_profile, cuda_api_profile


if __name__ == '__main__':
    gpu_kernel_profile, cuda_api_profile = parse_profile('citeseer-gin.csv')
    gpu_kernel_profile, cuda_api_profile = parse_profile('citeseer-gcn.csv')

    rc_init()
