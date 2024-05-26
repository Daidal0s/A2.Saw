#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <vector>

enum class ECandleClosePosition { Higher, Lower, Same };

class Core {
private:
	static bool compare(ECandleClosePosition expectation, int first, int second);
	static bool haveSaw(std::vector<int> &array);

public:
	explicit Core() = default;
	static int saw(std::vector<int> &arrayToCheckSaw);
	virtual ~Core() = default;
};

#endif	// CORE_H
