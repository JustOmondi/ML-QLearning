/**
         (                                      
   (     )\ )                                   
 ( )\   (()/(   (    ) (        (        (  (   
 )((_)   /(_)) ))\( /( )(   (   )\  (    )\))(  
((_)_   (_))  /((_)(_)|()\  )\ |(_) )\ )((_))\  
 / _ \  | |  (_))((_)_ ((_)_(_/((_)_(_/( (()(_) 
| (_) | | |__/ -_) _` | '_| ' \)) | ' \)) _` |  
 \__\_\ |____\___\__,_|_| |_||_||_|_||_|\__, |  
                                        |___/   

Refer to Watkins, Christopher JCH, and Peter Dayan. "Q-learning." Machine learning 8. 3-4 (1992): 279-292
for a detailed discussion on Q Learning
*/
#include "CQLearningController.h"

using namespace std;


CQLearningController::CQLearningController(HWND hwndMain):
	CDiscController(hwndMain),
	_grid_size_x(CParams::WindowWidth / CParams::iGridCellDim + 1),
	_grid_size_y(CParams::WindowHeight / CParams::iGridCellDim + 1)
{

}
/**
 The update method should allocate a Q table for each sweeper (this can
 be allocated in one shot - use an offset to store the tables one after the other)

 You can also use a boost multiarray if you wish
*/
void CQLearningController::InitializeLearningAlgorithm(void)
{
	//TODO

	int sweepers = CParams::iNumSweepers;
	int totalStates = _grid_size_x * _grid_size_y;

	// UP, DOWN, LEFT, RIGHT
	int numActions = 4;

	//initialize all sweepers' Q tables with 0s.
	for (int i = 0; i < sweepers; i++) 
	{
		vector<vector<double>> sweeperQTable;

		// Add a vector of actions for each state
		for (int j = 0; j < totalStates; j++)
		{
			vector<double> actions;

			// Set all actions to 0
			for (int k = 0; k < numActions; k++)
			{
				actions.push_back(0);
			}

			// Add vector of actions to sweeper's Q table
			sweeperQTable.push_back(actions);
		}

		// Add sweeper Q Table to Q tables vector
		QTables.push_back(sweeperQTable);
	}

}
/**
 The immediate reward function. This computes a reward upon achieving the goal state of
 collecting all the mines on the field. It may also penalize movement to encourage exploring all directions and 
 of course for hitting supermines/rocks!
*/
double CQLearningController::R(uint x,uint y, uint sweeper_no)
{
	// default reward is 0. No reward is given for an arbitrary position with no object
	double reward = 0;
	CDiscMinesweeper* sweeper = m_vecSweepers[sweeper_no];
	int objectAtCurrentIndex = sweeper->CheckForObject(m_vecObjects, CParams::dMineScale);

	// If object is valid
	if (objectAtCurrentIndex >= 0)
	{
		switch (m_vecObjects[objectAtCurrentIndex]->getType())
		{
			// Negative reward for colliding with a rock
			case CDiscCollisionObject::Rock:
				reward = -100;
				break;

			// Positive reward for finding a mine
			case CDiscCollisionObject::Mine:
				reward = 100;
				break;

			// Negative reward colliding with a super mine
			case CDiscCollisionObject::SuperMine:
				reward = -100;
				break;
		}

	}

	return reward;
}
/**
The update method. Main loop body of our Q Learning implementation
See: Watkins, Christopher JCH, and Peter Dayan. "Q-learning." Machine learning 8. 3-4 (1992): 279-292
*/
bool CQLearningController::Update(void)
{
	//m_vecSweepers is the array of minesweepers
	//everything you need will be m_[something] ;)
	uint cDead = std::count_if(m_vecSweepers.begin(),
							   m_vecSweepers.end(),
						       [](CDiscMinesweeper * s)->bool{
								return s->isDead();
							   });
	if (cDead == CParams::iNumSweepers)
	{
		printf("All dead ... skipping to next iteration\n");
		m_iTicks = CParams::iNumTicks;
	}

	for (uint sw = 0; sw < CParams::iNumSweepers; ++sw)
	{
		if (m_vecSweepers[sw]->isDead()) continue;

		//1:::Observe the current state:
		SVector2D<int> pos = m_vecSweepers[sw]->Position();
		pos /= 10;
		
		//2:::Select action with highest historic return:

		// Current position of sweeper in its Q Table = (xPos * yGridSize) + yPos
		int action = getMaxAction(QTables[sw][(pos.x * _grid_size_y) + pos.y]);

		ROTATION_DIRECTION direction;
		switch (action)
		{
			case 0:
				direction = ROTATION_DIRECTION::EAST;
				break;
			case 1:
				direction = ROTATION_DIRECTION::NORTH;
				break;
			case 2:
				direction = ROTATION_DIRECTION::WEST;
				break;
			case 3:
				direction = ROTATION_DIRECTION::SOUTH;
				break;
		}
		m_vecSweepers[sw]->setRotation(direction);
		//TODO
		//now call the parents update, so all the sweepers fulfill their chosen action
	}
	
	CDiscController::Update(); //call the parent's class update. Do not delete this.
	
	for (uint sw = 0; sw < CParams::iNumSweepers; ++sw){
		if (m_vecSweepers[sw]->isDead()) continue;
		//TODO:compute your indexes.. it may also be necessary to keep track of the previous state
		//3:::Observe new state:
		//TODO
		//4:::Update _Q_s_a accordingly:
		//TODO
	}
	return true;
}

int CQLearningController::getMaxAction(vector<double> actions)
{
	int maxAction = 0;

	// Intiialize the max value as the first action
	double maxValue = actions[0];

	// Update the max value as we loop through all the actions
	for (int i = 0; i < actions.size(); i++)
	{
		if (actions[i] > maxValue)
		{
			maxAction = i;
			maxValue = actions[i];
		}
	}

	// Vector to store max values in case there are actions with the same values
	vector<int> maxActions;

	// Get all the actions with max values (in case more than one action has the max value)
	for (int i = 0; i < actions.size(); i++)
	{
		if (actions[i] == maxValue)
		{
			maxActions.push_back(i);
		}
	}

	// Get one of the max actions randomly of there are more than one max actions
	if (maxActions.size() > 1)
	{
		int randomIndex = RandInt(0, maxActions.size() - 1);
		maxAction = maxActions[randomIndex];
	}
	else
	{
		maxAction = maxActions[0];
	}

	return maxAction;
}

CQLearningController::~CQLearningController(void)
{
	//TODO: dealloc stuff here if you need to	
}
