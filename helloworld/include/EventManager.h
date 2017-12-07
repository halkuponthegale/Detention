#pragma once
#include <map>
typedef void(*evCallback)(void);
class EventManager {
public:
	EventManager() {

	}
	void triggerEvent(std::string name) {
		for (auto const& x : events) {
			if (!(x.first.compare(name))) {
				x.second();
			}
		}
	}
	void registerEvent(std::string name, evCallback callback) {
		events.insert(std::pair<std::string,evCallback>(name,callback));
	}

private:
	std::map<std::string, void(*)(void)> events;
};
