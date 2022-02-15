#include <bits/stdc++.h>

using namespace std;

int main() {

	string in;
	vector<string> v;//放各行 input, 以一行為單位

	while(getline(cin, in) && in != "END_OF_GRAMMAR") {v.push_back(in);}

	map<char, set<char> > mp;
	map<char, bool> used;//紀錄該行是否已找到 firstset
	vector<pair<char, vector<string> > > data(v.size());

	//初步處理輸入
	for(int i = 0; i < v.size(); i++) {

		char nonterminal = v[i][0];//每一行(第 i 行)輸入的第 0 位就是 nonterminal
		used[nonterminal] = 0;
		data[i] = {nonterminal, {}};//創建一個分別紀錄 input 的 nonterminal 和 grammer 的空間

		string tmp = "";
		for(int j = 2; j < v[i].length(); j++) {
		    //把 grammer 以"|"分開
			if(v[i][j] == '|') {data[i].second.push_back(tmp); tmp = "";}
			else {tmp += v[i][j];}
		}
		data[i].second.push_back(tmp);
	}

	for(int k = 0; k < v.size(); k++) {
		for(int i = 0; i < v.size(); i++) if(used[v[i][0]] == 0) {//每一行 input 都執行一次

			bool ok = 1;//判斷該組可不可以找到 firstdet
			bool isempty = 0;//判斷整組 grammer 有沒有出現過";"(即 lambda)
			set<char> tmps;//set 是會自動幫忙排序的容器
			for(int j = 0; j < data[i].second.size(); j++) {//該行的 grammer 有幾個字就執行幾次

				string tmp = data[i].second[j];//tmp = 該行的 grammer
				bool empty = 1;//判斷該行 grammer 有沒有出現過";"(即 lambda)
				for(char c : tmp) {

					if(c == ';') {}
                    else if(islower(c) || c == '$') {//c 是 terminal
						tmps.insert(c);
						empty = 0;
						break;
					}
					else if(used[c] && mp[c].count(';')) {//c 已經被處理過至少一次, 且含有";"
						tmps.insert(mp[c].begin(), mp[c].end());
					}
					else if(used[c]) {//c 已經被處理過至少一次, 且不含";"
						empty = 0;
						tmps.insert(mp[c].begin(), mp[c].end());
						break;
					}
					else {
						ok = 0;//該組不可以找到 firstdet, 所以先跳過
						break;
					}
				}
				isempty |= empty;

			}
			if(ok) {//該行執行完畢
				used[v[i][0]] = 1;//標記:已被處理過一次
				mp[v[i][0]].insert(tmps.begin(), tmps.end());//把目前處理到一半的 firstset 存起來
				if(isempty) mp[v[i][0]].insert(';');
				else mp[v[i][0]].erase(';');
				break;
			}
		}
	}

	//輸出結果
	for(map<char, set<char>>::iterator it = mp.begin(); it != mp.end(); it++) {

		char c = it->first;//即將被輸出的 terminal
		set<char> st = it->second;//即將被輸出的 firstset 部分
		cout << c << ' ';

		if(st.count('$')) {st.erase(';');}
		for(set<char>::iterator sit = st.begin(); sit != st.end(); sit++) {cout << *sit;}
		cout << endl;
	}

	cout << "END_OF_FIRST\n";
}

/*


1. 點【.】
簡單來說，點可以代替所有可能的字元（字母、數字或符號）。

比如使用「.GC」，可以匹配的搜尋結果包括UGC（User Generated Content）、OGC（Occupationally Generated Content）、PGC（Professionally Generated Content）或是2GC、nGC等。



2. ? 【問號】
問號代表的意思是，比對前一個字串或是不比對。比如你在輸入facebook的時候可能不小心book少了一個o，那你使用規則運算式facebo?k，可能匹配的結果包括facebook（包括o）、facebok（不包括o）。



3. ＊【星號】
星號表示比對前一個字串零次或是多次。比方你輸入的「sky*blue」時，星好前面的字元為[y]，因此搜尋結果會出現skblue（y出現零次）、skyblue（y出現一次）、skyyyyblue（y出現很多次）。



4. + 【加號】
加號跟星號類似，差別在於它至少要與前一個字比對一次或以上。以上一個例子「sky*blue」來說，搜尋結果可能會出現「skblue」，但因為加號強制在前面的符號至少要比對一次，因此如果輸入「sky+blue」，就一定會出現至少一次y：「skyblue」，其他可能的結果跟輸入星號一樣。



5.｜【直線】
跟使用google搜尋引擎類似，規則運算式也有代表「或者」的符號，就是直線。比如你想要搜尋整個網站跟Facebook、Instagram、Wordpress、Google有關的文章之流量，你就可以使用 Facebook｜Instagram｜Wordpress｜Google 這樣的進階搜尋，為你想要的結果一次一網打盡。

又或者你有不同的產品，在網址的結尾分別使用thanks或是thankyou，那麼你也可以用/productname-thank （s｜kyou），一次查看完成產品購買的使用者的資訊。



6. ＾ 【插入符號】和 $【錢字符號】
^插入符號是比對前開頭，$錢字符號則是比對結尾。

比如你輸入的搜尋條件是 ^eat，那麼你會搜尋到的結果會有eat、eaten；如果是eat$，那麽搜尋到的結果可能是creat、peat、leat。如果你只想要搜尋eat這個字，那麼可以使用^eat＄，這將只鎖定符合「eat」的這個搜尋結果



7. \ 【反斜線】
將任何特殊字元，恢復成一般字元。

可能在搜尋特定網址的時候裡面有一個點或者是查找IP的時候也有一個點，可是這個點同時又在規則運算式裡面有它自己的功能，為了要讓這個點不受到規則運算的影響（不要使用規則運算裡「點」的功能），此時就需要反斜線的幫助。

比如我想找transbiz.com但如果只輸入transbiz.com的時候可能會出現的搜尋結果包括transbizkcom、transbizzcom、transbizccom⋯⋯所以為了更精準地找到你想要的結果，在規則運算式裡輸入「transbiz\.com」，就會出現transbiz.com了。

8. ( ) 【括號】
括號簡單來說就是把你想要找的相關字詞放在括號裡面，它就會依照括號裡面的字元排序為你找到可能的結果。比如 (sym)，你可能搜尋到的結果可能有sympathy、symbol、assym等。

而在使用上它常常會和｜（直線）一起搭配使用，比如 sy(m｜n)，你可能就會找到syndrome。



9. [ ] 【中括號】
任意比對字串中裡面的每個項目。比如你設定[DEFG]，那麼就會為你找出含有DEFG的相關內容，比如產品類別有A到Z，但你想看DEFG這幾個商品類別的表現，那麼就可以用product[DEFG]找到你要的商品：prdocutD、prdocutE、prdocutF、prdocutG。



10. – 【破折號】
常常會和中括號[]一起使用，比如product [A-K], product [3-9] 就可以分別叫出編號A到K、編號3到9的商品。

數量標示：標示某個符號或字集被允許出現的次數
{ } 數量符號
{10} 代表10個
{10, } 10個或以上
{1, 5} 1到5個之間
縮寫：
\w= [a-zA-Z]
\d =[0-9]
+ = {1, }
? = {0, 1}
* ={0,}

手機號碼：開頭到結尾都必須是數字，不得有連字符號
^[0-9]{10}$

郵遞區號：5碼數字
^[1-9]\d{4}$

身分證字號：一碼英文大寫搭配9碼數字
^[A-Z]\d{9}$

西元出身年月日：以1901/2/28表示
^\d{4}\/\d{1,2}\/\d{1,2}$
複雜版^[1-9]\d{3}\/[1]?\d\/[123]?\d$

*/

