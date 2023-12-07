#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include<set>
#include<map>
#include<algorithm>
using namespace std;

vector<vector<string>> flip(vector<vector<string>>v)
{
	vector<vector<string>>v2;
	vector<string>vec;
	vec.push_back("TiD"); vec.push_back("items");
	v2.push_back(vec);

	map<string, vector<string>>mp;
	set<string>st;
	for (int i = 1; i < v.size(); i++)
	{
		vector<string>tmp = v[i];
		string item = tmp[0];
		for (int j = 1; j < tmp.size(); j++)
		{
			string s = tmp[j];
			mp[s].push_back(item);
			st.insert(s);
		}
	}
	for (auto i : st)
	{
		vector<string>vec1;
		vec1.push_back(i);
		for (auto j : mp[i])
		{
			vec1.push_back(j);
		}
		v2.push_back(vec1);
	}
	return v2;
}
void display_data(vector<vector<string>>data)
{
	cout << "i will display the data now : " << endl;
	for (int i = 0; i < data.size(); i++)
	{
		cout << "the row number " << i + 1 << " : " << endl;
		vector<string>v;
		v = data[i];
		for (int j = 0; j < v.size(); j++)
		{
			cout << "string number " << j + 1 << " : " << v[j] << endl;
		}
	}
}
string clean_double_quote(string s)
{
	char a = '"';
	string s2 = "";
	for (int i = 0; i < s.size(); i++)
	{
		char c = s[i];
		if (c != a)
		{
			s2 += c;
		}
	}
	//cout << "iam returning : " << s2 << endl;
	return s2;
}
double lift_of(string s, map<pair<string, int>, bool>mp, int numberOfTransitions)
{
	vector<string>vec1; vector<string>vec2; vector<string>vec3;
	bool dash = false;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '>')
		{
			dash = true;
			continue;
		}
		if (dash == false)
		{
			string s1 = "";
			s1 += s[i];
			vec1.push_back(s1);
			vec3.push_back(s1);
		}
		else
		{
			string s1 = "";
			s1 += s[i];
			vec2.push_back(s1);
			vec3.push_back(s1);
		}
	}
	int all = 0, first_half = 0, second_half = 0;
	for (int i = 0; i < numberOfTransitions; i++)
	{
		bool flag = true;
		for (int j = 0; j < vec3.size(); j++)
		{
			if (mp[{vec3[j], i + 1}] == false)
			{
				flag = false;
			}
		}
		if (flag)
		{
			all += 1;
		}
	}
	for (int i = 0; i < numberOfTransitions; i++)
	{
		bool flag = true;
		for (int j = 0; j < vec1.size(); j++)
		{
			if (mp[{vec1[j], i + 1}] == false)
			{
				flag = false;
			}
		}
		if (flag)
		{
			first_half += 1;
		}
	}
	for (int i = 0; i < numberOfTransitions; i++)
	{
		bool flag = true;
		for (int j = 0; j < vec2.size(); j++)
		{
			if (mp[{vec2[j], i + 1}] == false)
			{
				flag = false;
			}
		}
		if (flag)
		{
			second_half += 1;
		}
	}
	double all_ = static_cast<double>(all) / numberOfTransitions;
	double first_half_ = static_cast<double>(first_half) / numberOfTransitions;
	double second_half_ = static_cast<double>(second_half) / numberOfTransitions;
	double answer = all_ / (first_half_ * second_half_);
	return answer;
}
bool try_inverse(string s, map<string, bool>mp)
{
	string s1 = "", s2 = "";
	bool dash = false;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '>')
		{
			dash = true;
			continue;
		}
		if (dash == false)
		{
			s1 += s[i];
		}
		else
		{
			s2 += s[i];
		}
	}
	string new_s = "";
	for (int i = 0; i < s2.size(); i++)
	{
		new_s += s2[i];
	}
	new_s += '>';
	for (int i = 0; i < s1.size(); i++)
	{
		new_s += s1[i];
	}
	return mp[new_s];

}
bool is_strong(string s, map<pair<string, int>, bool>mp, int numberOfTransitions, double confidence)
{
	bool flag = 1;
	vector<string>vec1;
	vector<string>vec2;
	bool arrow = false;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '>')
		{
			arrow = true;
			continue;
		}
		if (arrow == 0)
		{
			string str = "";
			str += s[i];
			vec1.push_back(str);
		}
		else
		{
			string str = "";
			str += s[i];
			vec2.push_back(str);
		}
	}
	int all = 0;
	for (int i = 0; i < numberOfTransitions; i++)
	{
		bool ok = 1;
		for (int j = 0; j < vec1.size(); j++)
		{
			if (mp[{vec1[j], i + 1}] == 0)
			{
				ok = 0;
			}
		}

		for (int j = 0; j < vec2.size(); j++)
		{
			if (mp[{vec2[j], i + 1}] == 0)
			{
				ok = 0;
			}
		}
		if (ok)
		{
			all += 1;
		}
	}
	int half = 0;
	for (int i = 0; i < numberOfTransitions; i++)
	{
		bool ok = 1;
		for (int j = 0; j < vec1.size(); j++)
		{
			if (mp[{vec1[j], i + 1}] == 0)
			{
				ok = 0;
			}
		}
		if (ok)
		{
			half += 1;
		}
	}

	double tmp = static_cast<double>(all) / half;
	if (tmp < confidence)
	{
		flag = 0;
	}

	return flag;
}
string fix(string s)
{
	set<char>st1;
	set<char>st2;
	bool flag = 0;
	for (int i = 0; i < s.size(); i++)
	{
		char c = s[i];
		if (c == '>')
		{
			flag = 1;
			continue;
		}
		if (flag == 0)
		{
			st1.insert(c);
		}
		else
		{
			st2.insert(c);
		}
	}
	string s2 = "";
	for (auto i : st1)
	{
		s2 += i;
	}
	s2 += '>';
	for (auto i : st2)
	{
		s2 += i;
	}
	return s2;
}
void extract_rules(string s, set<string>& st)
{
	int x = s.size();
	string s2;
	for (int i = 1; i < x; i++)
	{
		s2 = s;
		s2.insert(i, ">");
		s2 = fix(s2);
		st.insert(s2);
	}


}
string remove_dash(string s)
{
	string s2 = "";
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] != '-')
		{
			s2 += s[i];
		}
	}
	return s2;
}
void display(vector<vector<string>>v, vector<vector<string>>vec)
{
	for (int i = 0; i < v.size(); i++)
	{
		cout << "the candidates item sets of size " << i + 1 << " are : ";
		vector<string>vec2;
		vec2 = vec[i];
		for (int j = 0; j < vec2.size(); j++)
		{
			if (j == vec2.size() - 1)
			{
				cout << vec2[j];
			}
			else
			{
				cout << vec2[j] << " , ";
			}

		}
		cout << endl;
		cout << "the frequent item sets of size " << i + 1 << " are : ";
		vector<string>v2;
		v2 = v[i];
		for (int j = 0; j < v2.size(); j++)
		{
			if (j == v2.size() - 1)
			{
				cout << v2[j];
			}
			else
			{
				cout << v2[j] << " , ";
			}

		}
		cout << endl;
	}
}
string target_part(string s)
{
	int index = 0;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '-')
		{
			index = i;
		}
	}
	string s2 = "";
	for (int i = 0; i < index; i++)
	{
		s2 += s[i];
	}
	return s2;
}
bool is_common(string s, string s2)
{
	bool flag = 1;
	for (int i = 0; i < s.size(); i++)
	{
		if (s2[i] != s[i])
		{
			flag = 0;
		}
	}
	return flag;
}
void clear_it(string s, vector<string>& v)
{
	string now = "";
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] != '-')
		{
			now += s[i];
		}
		else
		{
			v.push_back(now);
			now = "";
		}
	}
	v.push_back(now);
}
void display_vector(vector<string>v)
{
	cout << "the vector has :";
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;
}


int main() {
	// Open the CSV file
	ifstream file("C:\\Users\\SIGMA\\Desktop\\Horizontal_Format.csv");

	// Check if the file is open
	if (!file.is_open()) {
		cerr << "Error opening file!" << endl;
		return 1;
	}

	// Define a vector to store each row of data
	vector<vector<string>> data;

	// Read the file line by line
	string line;
	while (getline(file, line)) {
		// Use a stringstream to split each line into tokens
		stringstream ss(line);
		vector<string> row;

		// Read each token separated by a comma
		string token;
		while (getline(ss, token, ',')) {
			row.push_back(token);
		}

		// Add the row to the data vector              
		data.push_back(row);
	}

	// Close the file
	file.close();

	for (int i = 0; i < data.size(); i++)
	{
		//clean every string in the data from double quoutes ""
		vector<string>v;
		v = data[i];
		for (int j = 0; j < v.size(); j++)
		{
			string s = v[j];
			v[j] = clean_double_quote(s);

		}
		data[i] = v;
	}
	if (data[0][0] != "TiD")
	{
		//chekc if the data is vertical
		data = flip(data);
	}

	//calcualate minimum support as minimum number of transactions
	double minimumSupport = 0;
	cout << "enter the minimum support as a percent ";
	cout << "for example if the support = 50" << '%' << " enter 0.5 :" << endl;
	cin >> minimumSupport;
	int numberOfTransitions = data.size() - 1;
	double value = minimumSupport * numberOfTransitions;
	int minimum_support = minimumSupport * numberOfTransitions;
	if (value > minimum_support)
	{
		minimum_support += 1;
	}
	vector<vector<string>>transitions;
	vector<string>uniqe_items;
	map<string, bool>inserted; //to check if the item has been added to the unique items or not yet
	map<string, int>mp; //to calculate the frequency of each item
	map<pair<string, int>, bool>mp2; //to konw if some item is present in some transaction
	vector<vector<string>>candidates;
	for (int i = 1; i < data.size(); i++)
	{
		//gather the unique items
		vector<string>v = data[i];
		for (int j = 1; j < v.size(); j++)
		{
			string s = v[j];
			if (inserted[s] == false)
			{
				uniqe_items.push_back(s);
				inserted[s] = 1;
			}

			if (mp2[{s, i }] == false)
			{
				mp[s] += 1;
			}
			mp2[{s, i }] = true;
		}
	}
	for (int i = 0; i < uniqe_items.size(); i++)
	{
		cout << "the item " << uniqe_items[i] << " has a frequency of : " << mp[uniqe_items[i]] << endl;
	}
	vector<vector<string>>frequentItemSets;
	candidates.push_back(uniqe_items);
	vector<string>frequent_items_size_1;
	for (auto i : uniqe_items)
	{
		// from the unique items gather the frequent items of size 1
		if (mp[i] >= minimum_support)
		{
			frequent_items_size_1.push_back(i);
		}
	}
	if (frequent_items_size_1.size() == 0)
	{
		cout << "there are no frequent items in the transactions" << endl;
		cout << "there are no strong rules in the transactions" << endl;
		return 0;
	}
	frequentItemSets.push_back(frequent_items_size_1);
	vector<string>frequent_items_size_2;
	vector<string>candidates_size_2;
	for (int i = 0; i < frequent_items_size_1.size(); i++)
	{
		for (int j = i + 1; j < frequent_items_size_1.size(); j++)
		{
			//generate frequent item sets of size 2 manually
			string s = frequent_items_size_1[i];
			string s2 = frequent_items_size_1[j];
			string str = ""; str += s; str += '-'; str += s2;
			candidates_size_2.push_back(str);
			int counter = 0;
			for (int h = 0; h < numberOfTransitions; h++)
			{
				if (mp2[{s, h + 1}] == true && mp2[{s2, h + 1}] == true)
				{
					counter += 1;
				}
			}
			if (counter >= minimum_support)
			{
				string S = "";
				S += s;
				S += "-";
				S += s2;
				frequent_items_size_2.push_back(S);
			}

		}
	}
	frequentItemSets.push_back(frequent_items_size_2);
	candidates.push_back(candidates_size_2);
	if (frequent_items_size_2.size() == 0)
	{
		display(frequentItemSets, candidates);
		cout << "there are no strong rules in the transactions" << endl;
		return 0;
	}
	bool flag = 1;
	while (flag)
	{
		//dynamically generate all frequent itemset of all sizes
		vector<string>new_v; //will store the candidates of the next size

		int number = frequentItemSets.size();
		number -= 1;
		vector<string>v = frequentItemSets[number];
		for (int i = 0; i < v.size(); i++)
		{
			string temp;
			string s = target_part(v[i]); // the target part is the first n-1 items of a transaction
			for (int j = i + 1; j < v.size(); j++)
			{
				temp = "";
				if (is_common(s, v[j]))
				{
					for (int z = s.size(); z < v[j].size(); z++)
					{
						temp += v[j][z];
					}
					string new_s = v[i] + temp;

					new_v.push_back(new_s);
				}
			}
		}
		candidates.push_back(new_v);
		vector<string>new_frequent;
		for (int i = 0; i < new_v.size(); i++)
		{
			//get all the items in the candidate itemset and check all transactions to see if it's frequent
			vector<string>vec; //will hold the items in the itemset without the dash
			clear_it(new_v[i], vec); //clears the '-' in the items sets for example a-b will be a b
			int counter = 0;
			for (int i2 = 0; i2 < numberOfTransitions; i2++)
			{
				bool little_flag = 1;
				for (int j = 0; j < vec.size(); j++)
				{
					string s = vec[j];
					if (mp2[{s, i2 + 1}] == false)
					{
						little_flag = 0;
					}
				}
				if (little_flag)
				{
					counter += 1;
				}

			}
			if (counter >= minimum_support)
			{
				new_frequent.push_back(new_v[i]);
			}
		}
		if (new_frequent.size() == 0)
		{
			flag = 0;
		}
		else
		{
			frequentItemSets.push_back(new_frequent);
		}

	}
	display(frequentItemSets, candidates);
	cout << "enter the minimum confidence as a percent : " << endl;
	double confidence;
	cin >> confidence;
	vector<set<string>>all_rules;
	for (int i = 1; i < frequentItemSets.size(); i++)//first vector has frequentItemSets of size one which won't have rules
	{
		vector<string>vec;
		vec = frequentItemSets[i];
		for (int j = 0; j < vec.size(); j++)
		{
			string s = vec[j];
			s = remove_dash(s);
			string new_s = s;
			sort(new_s.begin(), new_s.end());
			set<string>rules;
			int target = s.size(); //target is the number of rules that can be extracted of the itemset 
			target = pow(2, target);
			target -= 2;
			vector<string>all_combinations;
			all_combinations.push_back(new_s);
			while (next_permutation(new_s.begin(), new_s.end()))
			{
				all_combinations.push_back(new_s);
			}
			while (rules.size() < target)
			{
				for (int h = 0; h < all_combinations.size(); h++)
				{
					if (rules.size() >= target)
					{
						break;
					}
					string str = all_combinations[h];
					extract_rules(str, rules);// if we have (abc) we will get (a>bc , ab>c)

				}
			}
			all_rules.push_back(rules);
		}

	}
	vector<string>strong_rules;
	for (int i = 0; i < all_rules.size(); i++)
	{
		set<string>st = all_rules[i];
		for (auto j : st)
		{
			if (is_strong(j, mp2, numberOfTransitions, confidence))
			{
				strong_rules.push_back(j);
			}
		}
	}
	map<string, bool>lift_calculated;
	cout << "the dependencies between the rules are : " << endl;
	for (int i = 0; i < all_rules.size(); i++)
	{
		set<string>st;
		st = all_rules[i];
		for (auto j : st)
		{
			if (try_inverse(j, lift_calculated))
			{
				continue;
			}
			double lift = lift_of(j, mp2, numberOfTransitions);
			lift_calculated[j] = 1;
			cout << "in the rule : " << j << " ";
			if (lift > 1)
			{
				cout << "there is a positive dependency since the lift is : " << lift << endl;
			}
			else if (lift < 1)
			{
				cout << "there is a negative dependency since the lift is : " << lift << endl;
			}
			else
			{
				cout << "there is no dependecy since the lift is : " << lift << endl;
			}
		}
	}

	cout << "the strong rules are : " << endl;
	for (int i = 0; i < strong_rules.size(); i++)
	{
		cout << strong_rules[i] << endl;
	}

	return 0;
}
