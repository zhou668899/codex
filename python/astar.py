"""A simple A* search implementation for 4-directional grid maps."""

from __future__ import annotations

import heapq
from typing import Dict, Iterable, List, Optional, Tuple

Grid = List[List[int]]
Point = Tuple[int, int]


def manhattan(a: Point, b: Point) -> int:
    """Return Manhattan distance between two points."""
    return abs(a[0] - b[0]) + abs(a[1] - b[1])


def neighbors(point: Point, grid: Grid) -> Iterable[Point]:
    """Yield walkable neighbors of ``point`` on the grid."""
    rows, cols = len(grid), len(grid[0])
    row, col = point
    for dr, dc in ((1, 0), (-1, 0), (0, 1), (0, -1)):
        nr, nc = row + dr, col + dc
        if 0 <= nr < rows and 0 <= nc < cols and grid[nr][nc] == 0:
            yield (nr, nc)


def reconstruct_path(came_from: Dict[Point, Point], current: Point) -> List[Point]:
    """Reconstruct the path from the goal back to the start."""
    path: List[Point] = [current]
    while current in came_from:
        current = came_from[current]
        path.append(current)
    path.reverse()
    return path


def astar(grid: Grid, start: Point, goal: Point) -> Optional[List[Point]]:
    """Find the lowest-cost path between ``start`` and ``goal``.

    The grid must be a 2D list where ``0`` marks walkable tiles and any other
    value is treated as an obstacle. Returns ``None`` when no path exists.
    """

    if grid[start[0]][start[1]] != 0 or grid[goal[0]][goal[1]] != 0:
        return None

    open_heap: List[Tuple[int, int, Point]] = []
    heapq.heappush(open_heap, (manhattan(start, goal), 0, start))

    came_from: Dict[Point, Point] = {}
    g_score: Dict[Point, int] = {start: 0}

    while open_heap:
        _, cost, current = heapq.heappop(open_heap)
        if current == goal:
            return reconstruct_path(came_from, current)

        for neighbor in neighbors(current, grid):
            tentative_cost = cost + 1
            if tentative_cost < g_score.get(neighbor, float("inf")):
                came_from[neighbor] = current
                g_score[neighbor] = tentative_cost
                f_score = tentative_cost + manhattan(neighbor, goal)
                heapq.heappush(open_heap, (f_score, tentative_cost, neighbor))

    return None


def demo() -> None:
    grid = [
        [0, 0, 0, 0, 1, 0],
        [1, 1, 0, 0, 1, 0],
        [0, 0, 0, 0, 0, 0],
        [0, 1, 1, 1, 1, 0],
        [0, 0, 0, 0, 0, 0],
    ]
    start, goal = (0, 0), (4, 5)
    path = astar(grid, start, goal)
    print("Grid path:", path)


if __name__ == "__main__":
    demo()
