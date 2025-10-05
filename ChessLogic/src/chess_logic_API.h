#pragma once

#ifdef _WIN32
	#ifdef CHESSLOGIC_EXPORTS
		#define CHESSLOGIC_API __declspec(dllexport)
	#else
		#define CHESSLOGIC_API __declspec(dllimport)
	#endif // CHESSLOGIC_EXPORTS
#else
	#define CHESSLOGIC_API __attribute__((visibility("default")))
#endif
