#pragma once

#include <string>
#include <map>

using namespace std;

class SettingType {
public:
	enum Type {
		TYPE_NONE = 0,
		TYPE_BOOL,
		TYPE_INT,
		TYPE_UINT,
		TYPE_LONG,
		TYPE_ULONG,
		TYPE_LONG_LONG,
		TYPE_ULONG_LONG,
		TYPE_FLOAT,
		TYPE_DOUBLE,
		TYPE_LONG_DOUBLE,
		TYPE_STRING,
		TYPE_ARRAY,
		TYPE_LIST,
	};

	static string getTypeName(Type type) {
		static map<Type, string> map = {
				{ TYPE_NONE, "none" },
				{ TYPE_BOOL, "bool" },
				{ TYPE_INT, "int" },
				{ TYPE_UINT, "uint" },
				{ TYPE_LONG, "long" },
				{ TYPE_ULONG, "ulong" },
				{ TYPE_LONG_LONG, "llong" },
				{ TYPE_ULONG_LONG, "ullong" },
				{ TYPE_FLOAT, "float" },
				{ TYPE_DOUBLE, "double" },
				{ TYPE_LONG_DOUBLE, "double" },
				{ TYPE_STRING, "string" },
				{ TYPE_ARRAY, "array" },
				{ TYPE_LIST, "list" },
		};

		return map[type];
	}
};


