#include <algorithm>
#include <deque>
#include <iostream>
#include <map>
#include <numeric>
#include <vector>

class Speaker
{
public:
	std::string m_Name;
	int m_Score[3]; // 得分数组s
};

void create_speaker(std::vector<int>& v, std::map<int, Speaker>& m)
{
	const std::string name_seed = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	for (int i = 0; i < name_seed.size(); ++i)
	{
		std::string name = "选手";
		name += name_seed[i];
		Speaker speaker;
		speaker.m_Name = name;
		for (int j = 0; j < 3; ++j)
		{
			speaker.m_Score[j] = 0;
		}
		v.push_back(i + 100);
		m.insert(std::make_pair(i + 100, speaker));
	}
}

void speech_draw(std::vector<int>& v)
{
	std::random_shuffle(v.begin(), v.end());
}

void speech_context(int index, std::vector<int>& v1, std::map<int, Speaker>& m, std::vector<int>& v2)
{
	std::multimap<int, int, std::greater<>> group_map;
	int num = 0;
	for (auto it = v1.begin(); it != v1.end(); ++it)
	{
		num++;
		std::deque<int> d;
		for (int i = 0; i < 10; ++i)
		{
			int score = std::rand() % 41 + 60;
			d.push_back(score);
		}
		std::sort(d.begin(), d.end());
		d.pop_back();
		d.pop_front();
		const int sum = std::accumulate(d.begin(), d.end(), 0);
		int avg = sum / d.size();

		m[*it].m_Score[index - 1] = avg;

		group_map.insert(std::make_pair(avg, *it));

		if (num % 6 == 0)
		{
			/*std::cout << "小组比赛成绩如下: " << std::endl;

			for (auto pair : group_map)
			{
				std::cout << "编号: " << pair.second << "姓名: " << m[pair.second].m_Name << " 得分: " << m[pair.second].m_Score[index - 1] << std::endl;
			}*/

			int count = 0;
			for (auto mit = group_map.begin(); mit != group_map.end(), count < 3; count++, ++mit)
			{
				v2.push_back(mit->second);
			}

			group_map.clear();
		}
	}
}

void show_score(int index, std::vector<int>& v, std::map<int, Speaker>& m)
{
	std::cout << "第" << index << "轮 比赛成绩如下: " << std::endl;
	for (auto it = m.begin(); it != m.end(); ++it)
	{
		std::cout << "编号" << it->first << " 姓名" << it->second.m_Name << "分数: " << it->second.m_Score[index - 1] << std::endl;
	}

	std::cout << "晋级选手编号" << std::endl;
	std::for_each(v.begin(), v.end(), [](int val) {std::cout << val << std::endl; });
}

int main(int argc, char* argv[])
{
	std::vector<int> v1; // 选手编号
	std::map<int, Speaker>m; // 存放选手编号

	create_speaker(v1, m); // 创建选手

	for (int i = 0; i < 3; ++i)
	{
		speech_draw(v1); // 抽签
		std::vector<int> v; // 进入下一轮比赛的编号
		speech_context(i + 1, v1, m, v); // 比赛
		show_score(i + 1, v, m);
	}

	// 测试
	/*for (const auto& value : m)
	{
		std::cout << "编号" << value.first << " 姓名" << value.second.m_Name << std::endl;
	}*/

	return EXIT_SUCCESS;
}