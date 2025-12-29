// A* search for 4-directional grid maps.

function manhattan(a, b) {
  return Math.abs(a[0] - b[0]) + Math.abs(a[1] - b[1]);
}

function neighbors([row, col], grid) {
  const results = [];
  const rows = grid.length;
  const cols = grid[0].length;
  const deltas = [
    [1, 0],
    [-1, 0],
    [0, 1],
    [0, -1],
  ];

  for (const [dr, dc] of deltas) {
    const nr = row + dr;
    const nc = col + dc;
    if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] === 0) {
      results.push([nr, nc]);
    }
  }

  return results;
}

function reconstructPath(cameFrom, current) {
  const path = [current];
  while (cameFrom.has(key(current))) {
    current = cameFrom.get(key(current));
    path.push(current);
  }
  return path.reverse();
}

function key([r, c]) {
  return `${r},${c}`;
}

function astar(grid, start, goal) {
  if (grid[start[0]][start[1]] !== 0 || grid[goal[0]][goal[1]] !== 0) {
    return null;
  }

  const open = [];
  const cameFrom = new Map();
  const gScore = new Map([[key(start), 0]]);

  const push = (node, g) => {
    const f = g + manhattan(node, goal);
    open.push({ node, g, f });
    open.sort((a, b) => a.f - b.f);
  };

  push(start, 0);

  while (open.length > 0) {
    const { node: current, g: currentG } = open.shift();
    if (current[0] === goal[0] && current[1] === goal[1]) {
      return reconstructPath(cameFrom, current);
    }

    for (const next of neighbors(current, grid)) {
      const tentativeG = currentG + 1;
      const nextKey = key(next);
      const best = gScore.get(nextKey) ?? Number.POSITIVE_INFINITY;
      if (tentativeG < best) {
        cameFrom.set(nextKey, current);
        gScore.set(nextKey, tentativeG);
        push(next, tentativeG);
      }
    }
  }

  return null;
}

function demo() {
  const grid = [
    [0, 0, 0, 0, 1, 0],
    [1, 1, 0, 0, 1, 0],
    [0, 0, 0, 0, 0, 0],
    [0, 1, 1, 1, 1, 0],
    [0, 0, 0, 0, 0, 0],
  ];
  const start = [0, 0];
  const goal = [4, 5];
  const path = astar(grid, start, goal);
  console.log("Grid path:", path);
}

if (require.main === module) {
  demo();
}

module.exports = { astar, manhattan };
