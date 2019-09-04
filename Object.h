#pragma once

#include<string>

namespace daxie {
	//Every class is derived from Object.
	class Object {
	private:
		std::string str;

	public:
		Object();
		Object(const std::string& str);
		virtual ~Object();

	public:
		virtual std::string toString();
		void SetStr(const std::string& str);
	};
}