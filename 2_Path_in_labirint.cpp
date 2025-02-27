// Ограничение времени	1 секунда
// Ограничение памяти	64.0 Мб
// Ввод	in.txt
// Вывод	out.txt
// В заданном лабиринте найти путь между двумя данными узлами.

// Метод решения: Поиск в ширину.


//                            1
// Порядок просмотра          |
// узлов лабиринта        3 —   — 4
//                            |
//                            2
// Кодировка лабиринта: 1 — запрет; 0 — свободно.

// Формат ввода
// В первой строке число N — количество строк в лабиринте.
// Во второй строке число M — количество столбцов в лабиринте.
// Далее построчно расположен сам лабиринт. Затем располагаются координаты источника и цели в формате X Y,
// где X — номер строки, Y — номер столбца. Нумерация строк и столбцов начинается с единицы.

// Формат вывода
// В случае отсутствия пути в файл результатов необходимо записать "N".
// При наличии пути "Y" и далее весь путь.
// Маршрут должен начинаться координатами источника и заканчиваться координатами цели.
// Каждый шаг записывается с новой строки в формате X Y, где X — номер строки, Y — номер столбца.
// Нумерация строк и столбцов начинается с единицы.

// Пример
// Ввод              Вывод
// 4                 Y
// 5                 2 2
// 1 1 1 1 1         3 2
// 1 0 1 0 1         3 3
// 1 0 0 0 1         3 4
// 1 1 1 1 1         2 4
// 2 2
// 2 4

#include <iostream>
#include <queue>
#include <list>
#include <vector>

using std::cin, std::cout, std::queue, std::list, std::pair, std::vector, std::make_pair;

const char movement[4][2] = { {1, 0}, {-1, 0}, {0, -1}, {0, 1} };

list<int> bfs(vector<vector<int>>& lab, int N, int M, pair<int, int>& start,
	pair<int, int>& end, vector<vector<bool>>& visited, vector<vector<int>>& prevs)
{
	list<int> cages;
	queue<pair<int, int>> q;

	q.push(start);

	while (!q.empty())
	{
		pair<int, int> currentCage = q.front();
		q.pop();
		for (char i = 0; i < 4; ++i)
		{
			int nextX = currentCage.first + movement[i][0];
			int nextY = currentCage.second + movement[i][1];

			if (nextX >= N || nextY >= M) continue;

			if (nextX == end.first && nextY == end.second) 
			{
				prevs[nextX][nextY] = currentCage.first * M + currentCage.second;
				break;
			}

			if (!lab[nextX][nextY] && !visited[nextX][nextY]) 
			{
				q.push(make_pair(nextX, nextY));
				prevs[nextX][nextY] = currentCage.first * M + currentCage.second;
			}
		}
		visited[currentCage.first][currentCage.second] = true;
		if (prevs[end.first][end.second] != -1) break;
	}
	if (prevs[end.first][end.second] != -1)	
		for (int current = prevs[end.first][end.second]; current != -1; current = prevs[current / M][current % M]) 
			cages.push_front(current);

	return cages;
}

int main()
{
	freopen("in.txt", "r", stdin);

	int N, M; cin >> N >> M;
	vector<vector<int>> lab(N, vector<int>(M));
	
	for (int i = 0; i < N; ++i)
	{
		int val;
		for (int j = 0; j < M; ++j)
		{
			cin >> val;
			lab[i][j] = val;
		}
	}

	int startX, startY, endX, endY;
	cin >> startX >> startY >> endX >> endY;

	pair<int, int> start = make_pair(startX - 1, startY - 1), end = make_pair(endX - 1, endY - 1);
	vector<vector<bool>> visited(N, vector<bool>(M));
	vector<vector<int>> prevs(N, vector<int>(M, -1));
	
	list<int> cages = bfs(lab, N, M, start, end, visited, prevs);

	freopen("out.txt", "w", stdout);

	if (!cages.empty())
	{
		cout << "Y\n";
		for (int current : cages)
			cout << current / M + 1 << ' ' << current % M + 1 << '\n';

			cout << end.first + 1 << ' ' << end.second + 1;
	}
	else cout << "N";

	return 0;
}
