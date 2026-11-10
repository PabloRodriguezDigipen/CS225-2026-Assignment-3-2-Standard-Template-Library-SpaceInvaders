#include <AEEngine.h>
#include "Levels\Level 1.h"

int main()
{
	// Initialize the alpha engine
	if(AESysInit("CS255 - Space Invaders with Object Pooling") == false)
	{
		return 0;
	}

	// Add game states to the game state manager
	AEGameStateMgrAdd(
		GS_LEVEL_1,
		Level_1_Load,
		Level_1_Init,
		Level_1_Update,
		Level_1_Render,
		Level_1_Free,
		Level_1_Unload);

	// Initialize the game state manager with Space Invaders
	AEGameStateMgrInit(GS_LEVEL_1);

	// launch engine
	AESysGameLoop();

	// Terminate AECore
	AESysExit();

	return 0;
}
