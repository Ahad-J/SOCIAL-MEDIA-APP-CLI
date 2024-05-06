#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include<cstdlib>
using namespace std;
class MajorUsedFunctions
{
public:
	string user_file_path = "_user.txt";
	string page_file_path = "_page.txt";
	string friend_file_path = "_friend.txt";
	bool DuplicateCheck(string _file_path,string _search)
	{
		ifstream file(_file_path, ios::in);
		string _temp;
		while (file>>_temp)
		{
			if (_temp==_search)
			{
				return true;
			}
		}
		file.close();
		return false;
	}
	void Tokenizer(string &_n)
	{
		for (int i = 0; i < _n.length(); i++)
		{
			if (_n[i]==' ')
			{
				_n[i] = '_';
			}
		}
	}
	void Detokenizer(string &_n)
	{
		for (int i = 0; i < _n.length(); i++)
		{
			if (_n[i] == '_')
			{
				_n[i] = ' ';
			}
		}
	}
	string IDassigner(string parent_id,string child_id,string file_path)
	{
		srand(time(0));
		do
		{
			child_id = parent_id;
			child_id+= to_string(1 + rand() % 9999);
		} while (DuplicateCheck(file_path,child_id));
		return child_id;
	}
	string NextGetter(string _search, string file_path)
	{
		ifstream file(file_path, ios::in);
		string _temp;
		while (file>>_temp)
		{
			if (_temp==_search)
			{
				file >>_temp;
				file.close();
				return _temp;
			}
		}
	}
	int OccurenceCounter(string _search, string file_path)
	{
		int counter = 0;
		ifstream file(file_path, ios::in);
		string _temp;
		while (file >> _temp)
		{
			if (_temp == _search)
			{
				++counter;
			}
		}
		file.close();
		return counter;
	}
	template<class a>
	void getfriends(string file_path,a*ptr)
	{
		ptr->friend_list_counter = OccurenceCounter(ptr->ID, file_path);
		ptr->friend_list = new string * [ptr->friend_list_counter + 1];
		ifstream file(file_path, ios::in);
		string _temp;
		int index = 0;
		while (file >> _temp)
		{
			if (_temp == ptr->ID)
			{
				file >> _temp;
				ptr->friend_list[index] = new string(_temp);
				++index;
			}
		}
		file.close();
	}
	template<class b>
	void viewfriends(b* ptr)
	{
		for (int i = 0; i < ptr->friend_list_counter; i++)
		{
			cout << ptr->friend_list[i][0] << '\t' << NextGetter(ptr->friend_list[i][0].substr(2), user_file_path) << endl;
		}
	}
	template<class c>
	void addfriend(c* &ptr,string FRNDID)
	{
		if (DuplicateCheck(user_file_path,FRNDID))
		{
			FRNDID = "F-" + FRNDID;
			ofstream file(friend_file_path, ios::app);
			file << ptr->ID << ' ' << FRNDID << '\n';
			DeletePTR(ptr->friend_list, ptr->friend_list_counter);
			getfriends(friend_file_path, ptr);
		}
		else
		{
			cout << "User not found\n";
		}
	}
	void DeletePTR(string **& _array, int& _array_size)
	{
		for (int i = 0; i < _array_size; i++)
		{
			delete[]_array[i];
		}_array_size = 0;
	}

};


class User:public MajorUsedFunctions
{
public:
	string name = "default";
	string datatype = "USER-";
	string ID = "default";
	string** friend_list = nullptr;
	string** page_list = nullptr;
	string** post = nullptr;
	string** liked = nullptr;
	string** commented_posts = nullptr;

	int friend_list_counter = 0;
	int page_list_counter = 0;
	int post_counter = 0;
	int liked_counter = 0;
	int commented_posts_counter = 0;
	User()
	{
		ID=IDassigner(datatype,ID,user_file_path);
		cout << "Enter your name\n";
		getline(cin, name);
		cout << "Your unique ID is \t" << ID << endl;
		cout << "Remember your ID you can use it to acess the app\n";
		ofstream file(user_file_path, ios::app);
		Tokenizer(name);
		file << ID << ' ' << name << '\n';
		Detokenizer(name);
	}
	User(string _ID)
	{
		ID = _ID;
			name = NextGetter(_ID, user_file_path);
			Detokenizer(name);
	}
	~User() 
	{

	}


};
class Driver:public MajorUsedFunctions
{
public:
	User* Login()
	{
		User* temp = nullptr;
		cout << "Enter your ID\n";
		string _temp;
		getline(cin, _temp);
		if (DuplicateCheck(user_file_path, _temp))
		{
			cout << "User has been found\n";
			temp = new User(_temp);
			return temp;
		}
		else
		{
			cout << "No such user exist\n";
			return nullptr;
		}
	}
	User* Signup()
	{
		User* temp = new User;
		return temp;
	}
	void driver()
	{
		User* main = nullptr;
		main = Login();
		//main = Signup();
		getfriends(friend_file_path, main);
		viewfriends(main);
		addfriend(main, "USER-2001");
		viewfriends(main);
	}
};