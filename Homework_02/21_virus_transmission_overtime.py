def solve():
    # Read input
    N, K = map(int, input().split())
    S = list(map(int, input().split()))
    V = list(map(int, input().split()))

    # Convert to 0-based indexing
    K -= 1

    # Build adjacency list for who can meet whom
    adj = [[] for _ in range(N)]

    for i in range(N):
        for j in range(N):
            if i != j:
                # Check if runner i and j can meet
                if V[i] == V[j]:
                    # Same velocity - they meet only if starting at same position
                    if S[i] == S[j]:
                        adj[i].append(j)
                else:
                    # Different velocities - calculate meeting time
                    t = (S[j] - S[i]) / (V[i] - V[j])
                    if t >= 0:  # They meet at non-negative time
                        adj[i].append(j)

    # BFS/DFS to find all reachable runners from K
    visited = [False] * N
    queue = [K]
    visited[K] = True
    infected_count = 1

    while queue:
        current = queue.pop(0)
        for neighbor in adj[current]:
            if not visited[neighbor]:
                visited[neighbor] = True
                queue.append(neighbor)
                infected_count += 1

    return infected_count


# Test with the sample
def test_sample():
    # Sample input: N=6, K=3, S=[3,9,8,5,7,5], V=[6,6,5,4,6,3]
    N, K = 6, 3
    S = [3, 9, 8, 5, 7, 5]
    V = [6, 6, 5, 4, 6, 3]
    K -= 1  # Convert to 0-based

    adj = [[] for _ in range(N)]

    for i in range(N):
        for j in range(N):
            if i != j:
                if V[i] == V[j]:
                    if S[i] == S[j]:
                        adj[i].append(j)
                else:
                    t = (S[j] - S[i]) / (V[i] - V[j])
                    if t >= 0:
                        adj[i].append(j)

    # Find connected component starting from runner K (index 2)
    visited = [False] * N
    queue = [K]
    visited[K] = True
    infected_count = 1

    while queue:
        current = queue.pop(0)
        for neighbor in adj[current]:
            if not visited[neighbor]:
                visited[neighbor] = True
                queue.append(neighbor)
                infected_count += 1

    print(f"Infected count: {infected_count}")


# Run test
test_sample()

# Uncomment below to run with actual input
# print(solve())
