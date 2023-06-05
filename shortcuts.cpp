#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <utility>

int main() {

  // Reading the input

  int number_of_intersections;
  std::cin>>number_of_intersections;

  std::vector<int> next_portal(number_of_intersections);
  for (int intersection = 0; intersection < number_of_intersections; intersection++) {
    int portal_destination;
    std::cin>>portal_destination;

    // As the vector indices in C++ starts from 0
    portal_destination = portal_destination - 1;

    next_portal[intersection] = portal_destination;
  }


  // Necessary Data structures for Dijksrta algorithm 
  std::vector<bool> intersection_visited(number_of_intersections);
  std::vector<int> intersection_steps(number_of_intersections);
  std::set<std::pair<int, int>> bfs_set;

  intersection_visited[0] = true;
  intersection_steps[0] = 0;
  bfs_set.insert(std::make_pair(0, 0));

  while (!bfs_set.empty()) {
    int current_intersection = (*bfs_set.begin()).second;
    bfs_set.erase(bfs_set.begin());

    std::vector<int> possible_roads;

    // from each intersection, we can either use the portal or move to the neighbouring intersections.

    possible_roads.push_back(current_intersection - 1);
    possible_roads.push_back(current_intersection + 1);
    possible_roads.push_back(next_portal[current_intersection]);

    for (auto destination : possible_roads) {
      // checking if a better path is found. 
      if (destination < number_of_intersections && destination >= 0 && (!intersection_visited[destination] || intersection_steps[current_intersection] + 1 < intersection_steps[destination])) {
        intersection_visited[destination] = true;
        
        auto iterator_find = bfs_set.find(std::make_pair(intersection_steps[destination], destination));
        if (iterator_find != bfs_set.end()) bfs_set.erase(iterator_find);

        intersection_steps[destination] = intersection_steps[current_intersection] + 1;
        bfs_set.insert(std::make_pair(intersection_steps[destination], destination));
      }
    }

  }

  for (auto distance : intersection_steps) {
    std::cout << distance << std::endl;
  }

  return 0;
}