#include "validateQuery.h"
bool isAlphaCheck(std::string s) {
	bool check = true;
	for (int i = 0; i < s.length(); i++) {
		if (!(s[i] >= 65 && s[i] <= 90) && !(s[i] >= 97 && s[i] <= 122)) {
			check = false;
			std::cout << "Error, column or table name cannot contain any special character." << std::endl;
		}
	}
	return check;

}
bool isDataTypeCheck(std::string s) {
	if (s == "char" || s == "varchar" || s == "text" || s == "bool" || s == "int" || s == "float" || s == "datetime" || s == "date" || s == "year" || s == "time" || s == "timestamp") {
		return true;
	}
	return false;
}
bool isAvailable(std::string s) {
	if (s == "create"||s=="drop" || s == "table" || s == "insert" || s == "alter" || s == "update" || s == "order" || s == "having" || s == "not" || s == "null" || s == "references" || s == "on" || s == "use" || s == "delete" || s == "by" || s == "desc" || s == "asc" || s == "group" || s == "distinct" || s == "from" || s == "limit" || s == "where" || s == "in" || s == "like" || s == "values" || s == "into" || isDataTypeCheck(s)) {
		return false;
	}
	return true;
}

bool isdigit(std::string s) {
	for (int i = 0; i < s.length(); i++) {
		if (s[i] < 48 || s[i] > 57) {
			return false;
		}
	}
	return true;
}

bool validateQuery::validate(std::vector<std::string> v1) {
	bool check = true;
	for (int i = 0; i < v1.size(); i++) {
		std::transform(v1[i].begin(), v1[i].end(), v1[i].begin(), ::tolower);
	}

	int num = 0;
	int a=0;
	int count = 0;
	std::pair<std::string, std::string> column;
	for (int i = 0; i < v1.size(); i++) {
		std::cout << i + 1 << " : |" << v1[i] <<"|" << std::endl;
		if (v1[i] == "") {
			v1.pop_back();
		}
	}
	


	for (int i = 0; i<v1.size();i++) {
		try {
			if (v1.at(i) + v1.at(i + 1) == "createtable" && isAlphaCheck(v1.at(i + 2)) && v1.at(i + 2) != "(" && v1.at(i + 3) == "(") {
				std::cout << v1[i] << " " << v1[i + 1] << v1[i + 2] << v1[i + 3] << std::endl;
				query.first = v1[i + 2];
				a = i + 4;
				while (v1[a] != ")") {
					if (isAlphaCheck(v1.at(a)) && !isDataTypeCheck(v1.at(a)) && isDataTypeCheck(v1.at(a + 1))) {
						std::cout << v1.at(a) << " " << v1.at(a + 1) << " *" << a << " " << v1.size() << " " << v1.at(a + 2);
						column.first = v1.at(a);
						column.second = v1.at(a + 1);
						query.second.push_back(column);
						count++;
						if (v1.at(a + 2) == ",") {
							std::cout << v1[a + 2] << std::endl;
							a += 3;


						}
						else if (v1.at(a + 2) == ")") {
							std::cout << v1[a + 2] << std::endl;
							a += 2;

						}



						else if (v1.at(a + 2) + v1.at(a + 3) == "primarykey" /*&& (v1[a + 4] == "," || v1[a+4]==")")*/) {
							if (v1.at(a + 4) == ",") {
								std::cout << v1[a + 2] << " " << v1[a + 3] << v1[a + 4] << std::endl;
								a += 5;
							}
							else if (v1.at(a + 4) == ")") {
								std::cout << v1[a + 2] << " " << v1[a + 3] << v1[a + 4] << std::endl;
								a += 4;
							}
							else {
								check = false;
								break;
							}


						}


						else {
							check = false;
							break;
						}

					}
					else {
						check = false;
						break;
					}
					std::cout << v1[a] << std::endl;
				}

				if (v1.at(a + 1) == ";") {
					check = true;
					a++;
					std::cout << count << "\t" << query.second.size() << std::endl;
				}
				else {
					check = false;
				}


				i += a;
				std::cout << "index: " << i << std::endl;
				std::cout << "size: " << v1.size() << std::endl;
				std::cout << "**************" << v1.at(i) << "****************" << std::endl;
				std::cout << "check 1:" << check << std::endl;
				/*if (v1[i] == ";") {
					check = true;
					break;
				}*/

			}
			else if (v1.at(i) + v1.at(i + 1) == "insertinto" && isAlphaCheck(v1.at(i + 2)) && isAvailable(v1.at(i + 2)) && v1.at(i + 3) == "values")
			{std::cout << v1[i] << " " << v1[i + 1] << std::endl;
				a = 0;
				a = i + 4;
				int counter = 0;
				std::pair<std::string, std::string> p1;
				insertQuery.first = v1.at(i + 2);
				while (v1.at(a) != ";") {
					std::string s1;
					if (v1.at(a) == "(") {
						counter = a + 1;
						std::cout << "Counter at start: " << counter << std::endl;
						while (v1.at(counter) !=")") {
							if (v1.at(counter) != ",") {
								
									
									/*if (v1.at(counter - 1) == "'" ||(v1.at(counter - 2) == "'" && v1.at(counter) == "'")) {
										s1 = s1 + v1.at(counter);
									}
									else {
										s1 = s1 + ' ' + v1.at(counter);
									}*/
								if (v1.at(counter) == "'") {
									s1 = s1 + v1.at(counter++);
									do {
										s1 = s1 + v1.at(counter++);
									} while (v1.at(counter) != "'");
									s1 = s1 + v1.at(counter);
									p1.first = isdigit(v1.at(counter)) ? "int" : "char";
									p1.second = s1;
									std::cout << v1.at(counter) << std::endl;
								}
								else {
									std::cout << v1.at(counter) << std::endl;

									p1.first = isdigit(v1.at(counter)) ? "int" : "char";
									p1.second = v1.at(counter);
									

								}
								insertQuery.second.push_back(p1);
								s1.clear();
								
								/*insertQuery.second.at(counter).first = isdigit(v1.at(counter))?"int":"char";
								insertQuery.second.at(counter).second = v1.at(counter);*/

									
								
							}
							/*else {
								check = false;
								break;
							}*/
							
							counter++;
						}
						
						std::cout << s1 << std::endl;
						std::cout << counter << " "<<v1.at(counter)<<std::endl;
						if (v1.at(counter + 1) == ";") {
							a = counter+1;
						}
						else if (v1.at(counter + 1) == ",") {
							a = counter + 2;
						}
						else {
							check = false;
							break;
						}
						
						std::cout << v1.at(a) << std::endl;
						counter = 0;
						std::cout << std::endl;
						//s1.clear();
					}
					else {
						check = false;
						break;
					}
					
				}
				std::cout << v1.size() << std::endl;
				i += a;
			}
			else {
				check = false;
				std::cout << "check 3:" << check << std::endl;
				break;
			}
		}
		catch (...) {
			std::cout << "Error" << std::endl;
			check = false;
			break;
		}

	}
	
	std::cout << check << std::endl;
	return check;
}