#ifndef __ASTAR_HPP__
#define __ASTAR_HPP__

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// A C++ version of A* pathfinding algorithm from https://dotnetcoretutorials.com/2020/07/25/a-search-pathfinding-algorithm-in-c/
// Most of the comments from the original version are preserved and/or have minor modifications.
//
// This version uses smart pointers
namespace AStar
{
    template <typename T>
    using Smart = std::shared_ptr<T>;

    template <typename T, typename R = typename std::vector<T>::const_iterator>
    R Find(std::vector<T> &vector, T &key, bool F(T &, T &))
    {
        return std::find_if(vector.begin(), vector.end(), [&](T &f)
                            { return F(key, f); });
    }

    // Cartesian coordinates (see Path class below)
    class Point
    {
    public:
        int X;

        int Y;

        Point()
        {
        }

        Point(int x, int y)
        {
            X = x;

            Y = y;
        }
    };

    // Path found by A* algorithm
    class Path
    {
    public:
        // List of coordinates of the path
        std::vector<AStar::Point> Points;

        // String representation of the environment
        std::vector<std::string> Map;

        Path()
        {
        }

        // Helper function to mark path on map
        void Mark(const char c)
        {
            for (auto point = std::next(Points.begin()); point != --Points.end(); point++)
            {
                auto tile = *point;

                Map[tile.Y][tile.X] = c;
            }
        }
    };

    // Class representing a node in the graph
    class Node
    {
    public:
        int X;

        int Y;

        int Cost;

        int Distance;

        Smart<AStar::Node> Parent = nullptr;

        Node()
        {
        }

        Node(int x, int y, int cost, Smart<AStar::Node> &parent)
        {
            X = x;

            Y = y;

            Cost = cost;

            Parent = parent;
        }

        // Total cost to traverse this node
        int CostDistance()
        {
            return (Cost + Distance);
        }

        // The distance is essentially the estimated distance, ignoring obstacles to our target.
        // So how many nodes left and right, up and down, ignoring obstacles, to get there.
        //
        // Computes the 2D Manhattan Distance
        void SetDistance(Smart<AStar::Node> &node)
        {
            Distance = std::abs(node->X - X) + std::abs(node->Y - Y);
        }
    };

    typedef std::vector<Smart<AStar::Node>> Moves;

    bool IsPassable(std::vector<std::string> &map, int X, int Y, int mapX, int mapY, const char dst, const char passable)
    {
        return (X >= 0 && X <= mapX && Y >= 0 && Y <= mapY && (map[Y][X] == passable || map[Y][X] == dst));
    }

    // Get all traversible nodes from current node
    Moves Nodes(std::vector<std::string> &map, Smart<AStar::Node> &current, Smart<AStar::Node> &target, const char dst, const char passable)
    {
        // Define neighbors (X, Y): Up, Down, Left, Right
        std::vector<std::pair<int, int>> neighbors = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

        auto traversable = Moves();

        if (!map.empty())
        {
            auto mapX = map.front().length() - 1;

            auto mapY = map.size() - 1;

            for (auto &neighbor : neighbors)
            {
                auto index = 0;

                // Check if within map boundaries and if passable and/or leads to destination
                if (AStar::IsPassable(map, current->X + neighbor.first, current->Y + neighbor.second, mapX, mapY, dst, passable))
                {
                    traversable.push_back(std::make_shared<AStar::Node>(current->X + neighbor.first, current->Y + neighbor.second, current->Cost + 1, current));

                    traversable[index]->SetDistance(target);

                    index++;
                }
            }
        }

        return traversable;
    }

    bool Compare(Smart<AStar::Node> &a, Smart<AStar::Node> &b)
    {
        return a->X == b->X && a->Y == b->Y;
    }

    // Get index of node from a list
    Moves::const_iterator Find(Moves &nodes, Smart<AStar::Node> &node)
    {
        return AStar::Find(nodes, node, Compare);
    }

    // Remove node from list
    void Remove(Moves &nodes, Smart<AStar::Node> &node)
    {
        auto found = AStar::Find(nodes, node);

        if (found != nodes.end())
        {
            nodes.erase(found);
        }
    }

    // Check if node is on the list
    bool Is(Moves &nodes, Smart<AStar::Node> &node)
    {
        return AStar::Find(nodes, node) != nodes.end();
    }

    // Get coordinates of an object on the map
    void Coordinates(std::vector<std::string> &map, const char c, Smart<AStar::Node> &node)
    {
        for (auto i = 0; i < map.size(); i++)
        {
            auto result = map[i].find(c);

            if (result >= 0 && result < map[i].length())
            {
                node->X = result;

                node->Y = i;

                break;
            }
        }
    }

    // Find path from src to dst using the A* algorithm
    AStar::Path FindPath(std::vector<std::string> &map, const char src, const char dst, const char passable)
    {
        auto path = AStar::Path();

        if (!map.empty())
        {
            auto start = std::make_shared<AStar::Node>();

            AStar::Coordinates(map, src, start);

            auto end = std::make_shared<AStar::Node>();

            AStar::Coordinates(map, dst, end);

            start->SetDistance(end);

            // List of nodes to be checked
            auto active = Moves();

            // List of nodes already visited
            auto visited = Moves();

            active.push_back(start);

            while (!active.empty())
            {
                // Sort based on CostDistance
                std::sort(active.begin(), active.end(), [](Smart<AStar::Node> &src, Smart<AStar::Node> &dst)
                          { return src->CostDistance() < dst->CostDistance(); });

                auto check = active.front();

                if (check->X == end->X && check->Y == end->Y)
                {
                    // We found the destination and we can be sure (because of the sort order above)
                    // that it's the most low cost option.
                    auto node = check;

                    // Copy map
                    path.Map = map;

                    while (node)
                    {
                        path.Points.push_back(AStar::Point(node->X, node->Y));

                        node = node->Parent;
                    }

                    // Reverse list of coordinates so path leads from src to dst
                    std::reverse(path.Points.begin(), path.Points.end());

                    return path;
                }

                visited.push_back(check);

                AStar::Remove(active, check);

                auto nodes = AStar::Nodes(map, check, end, dst, passable);

                for (auto &node : nodes)
                {
                    // We have already visited this node so we don't need to do so again!
                    if (AStar::Is(visited, node))
                    {
                        continue;
                    }

                    // It's already in the active list, but that's OK, maybe this new node has a better value (e.g. We might zigzag earlier but this is now straighter).
                    if (AStar::Is(active, node))
                    {
                        auto existing = *AStar::Find(active, node);

                        if (existing->CostDistance() > node->CostDistance())
                        {
                            AStar::Remove(active, existing);

                            active.push_back(node);
                        }
                    }
                    else
                    {
                        // We've never seen this node before so add it to the list.
                        active.push_back(node);
                    }
                }
            }
        }

        return path;
    }
}
#endif
