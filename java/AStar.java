import java.util.*;

/** A* search for 4-directional grid maps. */
public class AStar {
    public record Point(int row, int col) {
        @Override
        public String toString() {
            return "(" + row + ", " + col + ")";
        }
    }

    private static int manhattan(Point a, Point b) {
        return Math.abs(a.row() - b.row()) + Math.abs(a.col() - b.col());
    }

    private static List<Point> neighbors(Point point, int[][] grid) {
        int rows = grid.length;
        int cols = grid[0].length;
        int[][] deltas = new int[][]{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        List<Point> results = new ArrayList<>();
        for (int[] delta : deltas) {
            int nr = point.row() + delta[0];
            int nc = point.col() + delta[1];
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] == 0) {
                results.add(new Point(nr, nc));
            }
        }
        return results;
    }

    private static List<Point> reconstruct(Map<Point, Point> cameFrom, Point current) {
        List<Point> path = new ArrayList<>();
        path.add(current);
        while (cameFrom.containsKey(current)) {
            current = cameFrom.get(current);
            path.add(current);
        }
        Collections.reverse(path);
        return path;
    }

    public static List<Point> astar(int[][] grid, Point start, Point goal) {
        if (grid[start.row()][start.col()] != 0 || grid[goal.row()][goal.col()] != 0) {
            return null;
        }

        Comparator<Node> comparator = Comparator.comparingInt(node -> node.fScore);
        PriorityQueue<Node> open = new PriorityQueue<>(comparator);
        Map<Point, Point> cameFrom = new HashMap<>();
        Map<Point, Integer> gScore = new HashMap<>();

        gScore.put(start, 0);
        open.add(new Node(start, manhattan(start, goal), 0));

        while (!open.isEmpty()) {
            Node current = open.poll();
            if (current.point.equals(goal)) {
                return reconstruct(cameFrom, current.point);
            }

            for (Point next : neighbors(current.point, grid)) {
                int tentative = current.gScore + 1;
                int best = gScore.getOrDefault(next, Integer.MAX_VALUE);
                if (tentative < best) {
                    cameFrom.put(next, current.point);
                    gScore.put(next, tentative);
                    int fScore = tentative + manhattan(next, goal);
                    open.add(new Node(next, fScore, tentative));
                }
            }
        }

        return null;
    }

    private record Node(Point point, int fScore, int gScore) {}

    public static void main(String[] args) {
        int[][] grid = new int[][]{
                {0, 0, 0, 0, 1, 0},
                {1, 1, 0, 0, 1, 0},
                {0, 0, 0, 0, 0, 0},
                {0, 1, 1, 1, 1, 0},
                {0, 0, 0, 0, 0, 0},
        };
        Point start = new Point(0, 0);
        Point goal = new Point(4, 5);
        List<Point> path = astar(grid, start, goal);
        System.out.println("Grid path: " + path);
    }
}
