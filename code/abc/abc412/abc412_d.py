from itertools import permutations

def get_cycles(n):
    # 全ての巡回置換による分割を列挙
    def dfs(remaining, current, res):
        if not remaining:
            res.append(current[:])
            return
        for l in range(3, len(remaining)+1):  # サイクルは3以上でなければならない
            for p in permutations(remaining, l):
                if min(p) != p[0]:  # 同型の重複サイクルを除く（回転対称）
                    continue
                dfs([x for x in remaining if x not in p], current + [list(p)], res)

    result = []
    dfs(list(range(1, n+1)), [], result)
    return result

def solve(N, M, edge_list):
    from itertools import combinations
    input_edges = set(tuple(sorted(e)) for e in edge_list)
    min_ops = float('inf')

    # サイクル分割を列挙
    all_partitions = get_cycles(N)

    for partition in all_partitions:
        new_edges = set()
        for cycle in partition:
            for i in range(len(cycle)):
                u = cycle[i]
                v = cycle[(i+1)%len(cycle)]
                new_edges.add(tuple(sorted((u, v))))
        ops = len(input_edges ^ new_edges)
        min_ops = min(min_ops, ops)
    
    return min_ops

# 入力処理
if __name__ == "__main__":
    N, M = map(int, input().split())
    edge_list = [tuple(map(int, input().split())) for _ in range(M)]
    print(solve(N, M, edge_list))
