#include <cstdint>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using std::cout;

using std::make_pair;

using std::string;

using std::map;
using std::unordered_map;

using std::vector;

struct PLTeam {
  string m_name;
  uint32_t m_pts;
  int32_t m_gd;
};

struct PLTeamRecord {
  uint32_t m_pos;
  uint32_t m_pts;
  int32_t m_gd;
};

int main() {
  vector<PLTeam> teams;
  teams.reserve(4);

  teams.emplace_back(
      PLTeam{.m_name = "Manchester City", .m_pts = 73, .m_gd = 44});
  teams.emplace_back("Arsenal", 71, 49);
  teams.emplace_back("Liverpool", 71, 41);
  teams.emplace_back("Aston Villa", 63, 19);

  for (uint32_t i = 0; i < teams.size(); ++i) {
    if (teams[i].m_name == "Liverpool") {
      cout << "Liverpool's league table position is " << i + 1 << "\n";
    }
  }

  // unordered_maps are faster than normal maps
  unordered_map<string, PLTeamRecord> team_records;

  // The `[]` operator in this case can be used to assign and insert
  // a key-value pair to the map, depending on if key exists or not.

  // team_records.emplace("Manchester City", PLTeamRecord{1, 73, 44});
  // team_records.emplace("Arsenal", PLTeamRecord{2, 71, 49});
  // team_records.emplace("Liverpool", PLTeamRecord{3, 71, 41});
  // team_records.emplace("Aston Villa", PLTeamRecord{4, 63, 19});
  team_records["Manchester City"] =
      PLTeamRecord{.m_pos = 1, .m_pts = 73, .m_gd = 44};
  team_records["Arsenal"] = PLTeamRecord{2, 71, 49};
  team_records["Liverpool"] = PLTeamRecord{3, 71, 41};
  team_records["Aston Villa"] = PLTeamRecord{4, 63, 19};

  cout << "\n";
  // Iterating through a map is slower than a vector
  for (auto &[name, record] : team_records) {
    cout << "Team name: " << name << "\n";
    cout << "Pts: " << record.m_pts << "\n\n";
  }
}