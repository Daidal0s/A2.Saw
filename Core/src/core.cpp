#include "core.h"


ECandleClosePosition switchClose(ECandleClosePosition sw) {
	switch (sw) {
		default:
			return sw;
		case ECandleClosePosition::Higher:
			return ECandleClosePosition::Lower;
		case ECandleClosePosition::Lower:
			return ECandleClosePosition::Higher;
	}
	return sw;
}

std::vector<int> findPossableSaws(std::vector<int> &vec) {
	std::vector<int> indexVector;
	std::vector<int> usedNumbers;
	std::unordered_map<int, std::vector<int>::iterator> mapIndex;

	int pair = -1;

	usedNumbers.push_back(-1);

	for (auto it = vec.begin(); it != vec.end(); ++it) {
		if (std::find(vec.begin(), vec.end(), *it) != vec.end()) {
			if (std::count(vec.begin(), vec.end(), *it) >= 2) {
				mapIndex[++pair] = std::find(vec.begin(), vec.end(), *it);
				mapIndex[++pair] = std::find(mapIndex[pair - 1] + 1, vec.end(), *it);
			}
			usedNumbers.push_back(*it);
		}
	}

	for (int iii = 0; iii < mapIndex.size(); iii += 2) {
		indexVector.push_back(static_cast<int>(mapIndex[iii] - vec.begin()));
		indexVector.push_back(static_cast<int>(mapIndex[iii + 1] - vec.begin()));
	}

	return indexVector;
}

bool Core::compare(ECandleClosePosition expectation, int first, int second) {
	switch (expectation) {
		case ECandleClosePosition::Higher:
			return (first > second);
			break;
		case ECandleClosePosition::Lower:
			return (first < second);
			break;
		case ECandleClosePosition::Same:
			return (first == second);
			break;
	}
	return false;
}

bool Core::haveSaw(std::vector<int> &array) {
	auto validPassCount = (static_cast<float>(array.size()) - 1.0) * 0.67;
	float passCounter = 0.0;

	std::vector<int>::iterator it;

	ECandleClosePosition candleClose = ECandleClosePosition::Higher;

	// Проверка первых значений

	if (compare(candleClose, array.at(0), array.at(1)))
		++passCounter;
	else
		candleClose = switchClose(candleClose);

	if (compare(candleClose, array.at(0), array.at(1))) 
		++passCounter;

	// Проверка оставшихся значений

	for (it = (array.begin() + 1); it == array.end(); ++it) {
		candleClose = switchClose(candleClose);
		if ((it + 1) != array.end() && compare(candleClose, *it, *(it)))
			++passCounter;
	}

	return passCounter > validPassCount;
}

int Core::saw(std::vector<int> &arrayToCheckSaw) {
	auto saws = findPossableSaws(arrayToCheckSaw);
	int sawSize = 0;

	if (saws.empty()) return 0;

	for (int iii = 0; iii < saws.size(); ++iii) {
		std::vector<int> govni(arrayToCheckSaw.begin() + saws.at(iii),
							   arrayToCheckSaw.begin() + saws.at(iii + 1));
		if (haveSaw(govni) && govni.size() > sawSize)
			sawSize = static_cast<int>(govni.size());
	}

	return sawSize;
}