#include <string>
#include <vector>
#include <fstream>

#if defined(USEV2)
#include "astarv2.hpp"
#else
#include "astar.hpp"
#endif

// Helper function to print coordinates
void Print(std::vector<AStar::Point> &points)
{
    for (auto i = 0; i < points.size(); i++)
    {
        std::cout << "(" << points[i].X << ", " << points[i].Y << ")";

        if (i < points.size() - 1)
        {
            if (points[i].X < points[i + 1].X)
            {
                std::cout << " R";
            }
            else if (points[i].X > points[i + 1].X)
            {
                std::cout << " L";
            }
            else if (points[i].Y < points[i + 1].Y)
            {
                std::cout << " D";
            }
            else if (points[i].Y > points[i + 1].Y)
            {
                std::cout << " U";
            }
        }

        std::cout << std::endl;
    }
}

// Helper function to print map
void Print(std::vector<std::string> &map)
{
    for (auto i = 0; i < map.size(); i++)
    {
        std::cout << map[i] << std::endl;
    }
}

int main(int argc, char **argv)
{
    auto map = std::vector<std::string>();

    if (argc > 1)
    {
        // Read map from a file
        std::string str;

        std::ifstream file(argv[1]);

        while (std::getline(file, str))
        {
            map.push_back(str);
        }
    }
    else
    {
        // Create default map
        map = {
            "A          ",
            "--| |------",
            "           ",
            "   |-----| ",
            "   |     | ",
            "---|     |B"};
    }

    std::cout << std::endl
              << "Initial Map:" << std::endl;

    // Print initial map without path
    Print(map);

    const char src = 'A';
    const char dst = 'B';
    const char passable = ' ';
    const char mark = '*';

    // Find path from src to dst using A*
    auto path = AStar::FindPath(map, src, dst, passable);

    // If path is found, the first and last elements of path.Points are the src and dst coordinates
    if (path.Points.size() > 0)
    {
        std::cout << std::endl
                  << "Path from " << src << " to " << dst << " (X, Y) required " << path.Points.size() - 1 << " step";

        if (path.Points.size() > 2)
        {
            std::cout << "s";
        }

        std::cout << ":" << std::endl;

        Print(path.Points);

        std::cout << std::endl
                  << "Map:" << std::endl;

        path.Mark(mark);

        Print(path.Map);
    }
    else
    {
        std::cout << std::endl
                  << "No path found!" << std::endl;
    }

    return 0;
}
