#include <bits/stdc++.h>
#include <chrono>
typedef long long ll;
using namespace std::chrono;
using namespace std;
#define P vector<vector<int>>
//N = 5
//M = 6
int rand(int a, int b) {
	return a + rand() % (b - a + 1);
}
int wyg(P &a) {
	for(int i = 3; i <= 5; i++) {
		for(int j = 0; j <= 6; j++) {
			int zw = a[i][j];
			for(int k = i; k > i - 3; k--) {
				if(a[k][j] != a[k - 1][j]) {
					zw = 0;
					break;
				}
			}
			if(zw > 0) {
				return zw;
			}
		}
	}
	for(int i = 0; i <= 5; i++) {
		for(int j = 0; j <= 3; j++) {
			int zw = a[i][j];
			for(int k = j; k < j + 3; k++) {
				if(a[i][k] != a[i][k + 1]) {
					zw = 0;
					break;
				}
			}
			if(zw > 0) {
				return zw;
			}
		}
	}
	for(int i = 3; i <= 5; i++) {
		for(int j = 0; j <= 3; j++) {
			int zw = a[i][j];
			for(int k = 0; k <= 2; k++) {
				if(a[i - k][j + k] != a[i - k - 1][j + k + 1]) {
					zw = 0;
					break;
				}
			}
			if(zw > 0) {
				return zw;
			}
		}
	}
	for(int i = 3; i <= 5; i++) {
		for(int j = 3; j <= 6; j++) {
			int zw = a[i][j];
			for(int k = 0; k <= 2; k++) {
				if(a[i - k][j - k] != a[i - k - 1][j - k - 1]) {
					zw = 0;
					break;
				}
			}
			if(zw > 0) {
				return zw;
			}
		}
	}
	return 0;
}
void wypisz(P &a) {
	cout << "STAN PLANSZY : \n";
	for(int i = 0; i < 6; i++) {
		for(int j = 0; j < 7; j++) {
			if(a[i][j] == 0) {
				cout << '.';
			}
			else if(a[i][j] == 1) {
				cout << 'o';
			}
			else {
				cout << 'x';
			}
		}
		cout << '\n';
	}
	cout << '\n';
	for(int j = 0; j < 7; j++) {
		cout << j;
	}
	cout << '\n';
}
bool wykonaj(P &a, int kt, int nr) {
	for(int i = 5; i >= 0; i--) {
		if(!a[i][kt]) {
			a[i][kt] = nr;
			return 1;
		}
	}
	return 0;
}
int zk = 0;
int eval(P &a, int nr, int LOS) {
	zk++;
	int ans = 0;
	int cnt = 0;
	int tmpnr = 1;
	if(nr == 1) {
		tmpnr = 2;
	}
	for(int l = 1; l <= LOS; l++) {
		P tmp = a;
		int cnt1 = 0, cnt2 = 0;
		for(auto x : a) {
			for(auto y : x) {
				if(y == 1) {
					cnt1++;
				}
				if(y == 2) {
					cnt2++;
				}
			}
		}
		int k;
		if(cnt1 > cnt2) {
			k = 2;
		}
		else {
			k = 1;
		}
		while(!wyg(tmp)) {
			//wypisz(tmp);
			vector<int>kt;
			for(int j = 0; j < 7; j++) {
				for(int i = 0; i < 6; i++) {
					if(!tmp[i][j]) {
						kt.push_back(j);
						break;
					}
				}
			}
			//for(auto x : kt) {
				//cout << x << ' ';
			//}
			//cout << '\n';
			if(!kt.size()) {
				break;
			}
			wykonaj(tmp, kt[rand(0, kt.size() - 1)], k);
			if(k == 1) {
				k = 2;
			}
			else {
				k = 1;
			}
		}
		int x = wyg(tmp);
		if(x == nr) {
			cnt++;
		}
		if(x > 0 && x != nr) {
			cnt--;
		}
	}
	ans = cnt * 10;
	cnt = 0;
	int zap = 0;
	for(int i = 0; i < 6; i++) {
		for(int j = 0; j < 7; j++) {
			if(a[i][j] == nr) {
				zap++;
				cnt += min(i + 1, 7 - i) + min(i + 1, 6 - i);
			}
			if(a[i][j] > 0 && a[i][j] != nr) {
				cnt -= (min(i + 1, 7 - i) + min(i + 1, 6 - i));
			}
		}
	}	
	if(!zap) {
		zap = 1;
	}
	ans += cnt * (21 / zap);
	cnt = 0;
	for(int i = 0; i < 6; i++) {
		for(int j = 0; j < 4; j++) {
			if(!a[i][j] && !a[i][j + 1] && a[i][j + 2] == nr && a[i][j + 3] == nr) {
				cnt++;
			}
			if(!a[i][j] && !a[i][j + 1] && a[i][j + 2] == tmpnr && a[i][j + 3] == tmpnr) {
				cnt--;
			}
		}
	}
	for(int i = 0; i < 6; i++) {
		for(int j = 0; j < 4; j++) {
			if(!a[i][j] && a[i][j + 1] == nr && a[i][j + 2] == nr && !a[i][j + 3]) {
				cnt++;
			}
			if(!a[i][j] && a[i][j + 1] == tmpnr && a[i][j + 2] == tmpnr && !a[i][j + 3]) {
				cnt--;
			}
		}
	}
	for(int i = 0; i < 6; i++) {
		for(int j = 0; j < 4; j++) {
			if(a[i][j] == nr && a[i][j + 1] == nr && !a[i][j + 2] && !a[i][j + 3]) {
				cnt++;
			}
			if(a[i][j] == tmpnr && a[i][j + 1] == tmpnr && !a[i][j + 2] && !a[i][j + 3]) {
				cnt--;
			}
		}
	}
	ans += cnt * 5;
	cnt = 0;
	for(int i = 0; i < 6; i++) {
		for(int j = 0; j < 4; j++) {
			if(a[i][j] == nr && a[i][j + 1] == nr && a[i][j + 2] == nr && !a[i][j + 3]) {
				cnt++;
			}
			if(a[i][j] == tmpnr && a[i][j + 1] == tmpnr && a[i][j + 2] == tmpnr && !a[i][j + 3]) {
				cnt--;
			}
		}
	}
	for(int i = 0; i < 6; i++) {
		for(int j = 0; j < 4; j++) {
			if(!a[i][j] && a[i][j + 1] == nr && a[i][j + 2] == nr && a[i][j + 3] == nr) {
				cnt++;
			}
			if(!a[i][j] && a[i][j + 1] == tmpnr && a[i][j + 2] == tmpnr && a[i][j + 3] == tmpnr) {
				cnt--;
			}
		}
	}
	for(int i = 0; i < 6; i++) {
		for(int j = 0; j < 3; j++) {
			if(!a[i][j] && a[i][j + 1] == nr && a[i][j + 2] == nr && a[i][j + 3] == nr && !a[i][j + 4]) {
				cnt += 2;
			}
			if(!a[i][j] && a[i][j + 1] == tmpnr && a[i][j + 2] == tmpnr && a[i][j + 3] == tmpnr && !a[i][j + 4]) {
				cnt -= 2;
			}
		}
	}
	ans += cnt * 20;
	cnt = 0;
	return ans;
}
int rek(P &a, int nr, int tp, int ile, int alfa, int beta, int LOS) {
	bool czy = 1;
	for(int i = 0; i < 6; i++) {
		for(int j = 0; j < 7; j++) {
			if(!a[i][j]) {
				czy = 0;
			}
		}
	}
	if(czy) {
		return 0;
	}
	int x = wyg(a);
	if(x) {
		if(x == nr) {
			return 1e9;
		}
		return -1e9;
	}
	if(!ile) {
		return eval(a, nr, LOS);
	}
	if(tp == 0) {
		int mx = -1e9;
		for(int j = 0; j < 7; j++) {
			P tmp = a;
			int k;
			if(j & 1) {
				k = 3 + (j + 1) / 2;
			}
			else {
				k = 3 - (j + 1) / 2;
			}
			if(wykonaj(tmp, k, nr)) {
				mx = max(mx, rek(tmp, nr, 1, ile - 1, alfa, beta, LOS));
			}
			alfa = max(alfa, mx);
			if(mx >= beta) {
				return mx;
			}
		}
		return mx;
	}
	int mn = 1e9;
	int tmpnr = 1;
	if(nr == 1) {
		tmpnr = 2;
	}
	for(int j = 0; j < 7; j++) {
		P tmp = a;
		int k;
		if(j & 1) {
			k = 3 + (j + 1) / 2;
		}
		else {
			k = 3 - (j + 1) / 2;
		}
		if(wykonaj(tmp, k, tmpnr)) {
			mn = min(mn, rek(tmp, nr, 0, ile - 1, alfa, beta, LOS));
		}
		beta = min(beta, mn);
		if(mn <= alfa) {
			return mn;
		}
	}
	return mn;
}
int ruch(P &a, int nr, int DEPTH, int LOS) {
	int kt = 0;
	int mx = -1e9;
	for(int j = 0; j < 7; j++) {
		P tmp = a;
		if(wykonaj(tmp, j, nr)) {
			int x = rek(tmp, nr, 1, DEPTH, -1e9, 1e9, LOS);
			if(x >= mx) {
				mx = x;
				kt = j;
			}
		}
	}
	cout << mx << '\n';
	return kt;
}
int main(int argc, char** argv) {
	srand(atoi(argv[1]));
	vector<vector<int> >akt(6);
	for(int i = 0; i < 6; i++) {
		akt[i] = vector<int>(7, 0);
	}
	cout << "KTO MA ZACZYNAC : GRACZ/BOT ?\n";
	string c;
	cin >> c;
	if(c[0] == 'G' || c[0] == 'g') {
		wypisz(akt);
		int k = 1;
		while(!wyg(akt)) {
			if(wyg(akt)) {
				break;
			}
			cout << "PODAJ LICZBE OD 0 DO 6\n";
			int x;
			cin >> x;
			//x--;
			wykonaj(akt, x, 1);
			wypisz(akt);
			auto start = high_resolution_clock::now();
			if(42 - 2 * (k - 1) < 9) {
				for(int i = 0; i < 42 - 2 * (k - 1); i++) {
					x = ruch(akt, 1, i, 16);
					auto stop = high_resolution_clock::now();
					auto duration = duration_cast<microseconds>(stop - start);
					ll tim = duration.count();
					if(tim > 700000) {
						break;
					}
				}
			}
			else {
				for(int i = 6; i < 42 - 2 * (k - 1); i++) {
					x = ruch(akt, 1, i, 16);
					auto stop = high_resolution_clock::now();
					auto duration = duration_cast<microseconds>(stop - start);
					ll tim = duration.count();
					if(tim > 700000) {
						break;
					}
				}
			}
			wykonaj(akt, x, 2);
			cout << "BOT ZAGRAL DO KOLUMNY NR : " << x << '\n';
			wypisz(akt);
			k++;
		}
	}
	else {
		int k = 1;
		while(!wyg(akt)) {
			int x;
			auto start = high_resolution_clock::now();
			if(42 - 2 * (k - 1) < 9) {
				for(int i = 0; i < 42 - 2 * (k - 1); i++) {
					x = ruch(akt, 1, i, 16);
					auto stop = high_resolution_clock::now();
					auto duration = duration_cast<microseconds>(stop - start);
					ll tim = duration.count();
					if(tim > 700000) {
						break;
					}
				}
			}
			else {
				for(int i = 6; i < 42 - 2 * (k - 1); i++) {
					x = ruch(akt, 1, i, 16);
					auto stop = high_resolution_clock::now();
					auto duration = duration_cast<microseconds>(stop - start);
					ll tim = duration.count();
					if(tim > 700000) {
						break;
					}
				}
			}
			wykonaj(akt, x, 1);
			cout << "BOT ZAGRAL DO KOLUMNY NR : " << x << '\n';
			wypisz(akt);
			if(wyg(akt)) {
				break;
			}
			cout << "PODAJ LICZBE OD 0 DO 6\n";
			x;
			cin >> x;
			//x--;
			wykonaj(akt, x, 2);
			wypisz(akt);
			k++;
		}
	}
}
