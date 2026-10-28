import sys
from math import gcd

def solve():
    # Read all inputs from standard input
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    n = int(input_data[0])
    K = int(input_data[1])
    
    idx = 2
    goods = []
    for _ in range(n):
        w = int(input_data[idx])
        v = int(input_data[idx+1])
        goods.append((w, v))
        idx += 2
        
    tiers = []
    for _ in range(K):
        L = int(input_data[idx])
        f = int(input_data[idx+1])
        tiers.append((L, f))
        idx += 2

    # Sort goods by value/weight ratio descending: v1/w1 > v2/w2 => v1*w2 > v2*w1
    # Python's built-in sort is stable and fast. We can use a key.
    # To avoid float issues in sorting, we can use a custom class or lambda with floats (since 64-bit float precision handles it well enough for sorting ratios, but cross-multiplication is safer).
    # Since we need to calculate exact fractions later, sorting by v/w as float is practically safe here due to distinct thresholds, but let's use a robust key.
    goods.sort(key=lambda x: x[1] / x[0], reverse=True)

    total_val_num = 0
    total_val_den = 1
    
    # We will accumulate total_value * scaling_factor and total_freight * scaling_factor
    # Or more simply: just track total revenue and total cost directly using fractions.
    # To keep code clean and fast, we can accumulate revenue and cost as exact fractions.
    
    net_p_num = 0
    net_p_den = 1
    
    def add_fraction(n1, d1, n2, d2):
        # returns (n1/d1) + (n2/d2) simplified
        common_den = d1 * d2
        num = n1 * d2 + n2 * d1
        g = gcd(num, common_den)
        return num // g, common_den // g

    # Initialize pointers
    good_idx = 0
    tier_idx = 0
    
    rem_good_w = goods[0][0] if n > 0 else 0
    rem_tier_w = tiers[0][0] if K > 0 else 0
    
    total_revenue_num = 0
    total_revenue_den = 1
    
    total_cost_num = 0
    total_cost_den = 1

    while good_idx < n and tier_idx < K:
        w_i, v_i = goods[good_idx]
        L_k, f_k = tiers[tier_idx]
        
        # Current amount we can ship in this step
        take_w = min(rem_good_w, rem_tier_w)
        
        # Check if this step is profitable: v_i / w_i > f_k  =>  v_i > f_k * w_i
        if v_i <= f_k * w_i:
            # Since goods' values are decreasing and tier costs are increasing,
            # no future pairings will be profitable. We stop here.
            break
            
        # Revenue added: take_w * (v_i / w_i)
        # Cost added: take_w * f_k
        
        # Update exact revenue fraction
        total_revenue_num, total_revenue_den = add_fraction(
            total_revenue_num, total_revenue_den, 
            take_w * v_i, w_i
        )
        
        # Update exact cost fraction
        total_cost_num, total_cost_den = add_fraction(
            total_cost_num, total_cost_den, 
            take_w * f_k, 1
        )
        
        # Deduct weight from current good and current tier
        rem_good_w -= take_w
        rem_tier_w -= take_w
        
        if rem_good_w == 0:
            good_idx += 1
            if good_idx < n:
                rem_good_w = goods[good_idx][0]
                
        if rem_tier_w == 0:
            tier_idx += 1
            if tier_idx < K:
                rem_tier_w = tiers[tier_idx][0]

    # Calculate Net Profit = Revenue - Cost
    # P/Q = (rev_num * cost_den - cost_num * rev_den) / (rev_den * cost_den)
    p_num = total_revenue_num * total_cost_den - total_cost_num * total_revenue_den
    p_den = total_revenue_den * total_cost_den
    
    # Simplify the fraction
    if p_num <= 0:
        print("0/1")
    else:
        g = gcd(p_num, p_den)
        print(f"{p_num // g}/{p_den // g}")

if __name__ == '__main__':
    solve()
