// Ограничение времени	1 секунда
// Ограничение памяти	64.0 Мб
// Ввод	in.txt
// Вывод	out.txt

// Определить, является ли данный граф ацикличным.

// Метод решения: Поиск в глубину.

// Формат ввода
// Первая строка содержит единственное число N — количество вершин в графе.
// Далее последовательно расположены списки смежностей для каждой вершины.
// Каждый список заканчивается 0. Вершины нумеруются с единицы.

// Формат вывода
// Для ацикличного графа файл ответа должен содержать единственный символ: "A"(латинское).
// Если в графе есть цикл, то в первой строке "N", во второй упорядоченный по возрастанию
// номеров список вершин, входящих в первый найденный цикл. Нумерация вершин графа начинается с единицы.

// Пример
// Ввод          Вывод
// 4             N
// 2 3 0         1 2 3
// 1 3 0
// 1 2 4 0
// 3 0

#include <iostream>
#include <climits>
#include <vector>
#include <list>

using std::string, std::vector, std::cin, std::cout, std::list;

void dfs(vector<vector<int>>& graph, int current, int prev, vector<char>& visited, list<int>& route, int& first, int& last)
{
	visited[current] = 1;
	for (int to : graph[current])
	{
		if (visited[to] == 0)
		{
			dfs(graph, to, current, visited, route, first, last);
			if (last < INT_MAX)
			{
				if (route.front() != first)
					route.push_front(current);
				return;
			}
		}
		else if (visited[to] == 1 && prev != to)
		{
			first = to;
			last = current;
			route.push_front(last);
			return;
		}
	}
	visited[current] = 2;
}

int main() 
{
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);

	int N; cin >> N;

	vector<vector<int>> graph(N);
	for (int i = 0; i < N; ++i)
	{
		int vert;
		while (cin >> vert && vert)
			graph[i].push_back(vert - 1);
	}

	vector<char> visited(N);
	list<int> route;
	int first = -1;
	int last = INT_MAX;

	for (int i = 0; last == INT_MAX && i < N; ++i)
		if (visited[i] == 0)
			dfs(graph, i, INT_MAX, visited, route, first, last);
	

	if (last != INT_MAX)
	{
		cout << "N\n";
		route.sort();
		last = route.back();
		route.pop_back();
		for (auto it = route.begin(); it != route.end(); ++it)
			cout << *it + 1 << ' ';
		cout << last + 1;
	}
	else cout << "A";

	return 0;
}
