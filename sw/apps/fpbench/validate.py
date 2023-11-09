#!/usr/bin/python3

import argparse
import os
import re

import pandas as pd


def parse(content):
    time = int(re.findall(r'TIME: (\d+)', content)[0])
    values = list(map(lambda s: float(s), re.findall(r'Values Begin\n([\s\S]*)\nValues End', content)[0].split('\n')))
    return {'time': time, 'values': values}

def validate(bench, truth):
    with open(os.path.join(args.outdir, bench, 'stdout', 'uart')) as f:
        bench_out = parse(f.read())
    with open(os.path.join(args.outdir, truth, 'stdout', 'uart')) as f:
        truth_out = parse(f.read())

    assert(len(bench_out['values']) == len(truth_out['values']))

    rel_err = 0
    for bench_val,truth_val in zip(bench_out['values'], truth_out['values']):
        if truth_val == 0:
            rel = 1 if bench_val != 0 else 0
        else:
            rel = min(1, abs(bench_val-truth_val)/abs(truth_val))
        rel_err += rel
    rel_err /= len(truth_out['values'])
    speedup = truth_out['time'] / bench_out['time']
    return {'rel_err': rel_err, 'speedup': speedup}



parser = argparse.ArgumentParser(description='FPbench validator')
parser.add_argument('outdir', type=str, help="path to cmake output directory")
parser.add_argument('benchmarks', type=str, nargs='+', help="names of the benchmarks")
args = parser.parse_args()

table = []

for bench in args.benchmarks:
    posit_res = validate(bench, bench + ".float")
    fixp_res  = validate(bench + ".fixp", bench + ".float")
    table.append({
        'name': bench,
        'posit.rel_err': posit_res['rel_err'], 'fixp.rel_err': fixp_res['rel_err'],
        'posit.speedup': posit_res['speedup'], 'fixp.speedup': fixp_res['speedup'],
    })

table = pd.DataFrame(table)
print(table.to_string(columns=["name", "posit.rel_err", "fixp.rel_err", "posit.speedup", "fixp.speedup"],
    formatters={"posit.rel_err": '{:,.5%}'.format, "fixp.rel_err": '{:,.5%}'.format }))

