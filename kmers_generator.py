import json

kmer_len = 5
input_file = "../data/hg38.fa"
output_file = "5mers_from_python.json"

kmer_dict = dict()
w = ''

with open(input_file) as f:
    while True:
        try:
            if len(w)<=kmer_len:
                l = f.readline()
                if l[0] == '>':
                    print(l)
                    continue
                l = l.upper().strip()
                w += l
            else:
                kmer_value = w[0:kmer_len]
                if kmer_value in kmer_dict.keys():
                    kmer_dict[kmer_value] += 1
                else:
                    kmer_dict[kmer_value] = 1
                w = w[1:]
        except:
            break

print("Writing to a JSON file ...")
with open(output_file, 'w') as fp:
    json.dump(kmer_dict, fp, indent=2)

print("Code completed sucessfully!")