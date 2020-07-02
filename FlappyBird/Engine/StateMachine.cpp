#include "StateMachine.hpp"

namespace Engine
{
	StateMachine::StateMachine()
		: _isRemoving(false), 
		_isAdding(false)
	{
		
	}

	StateMachine::~StateMachine()
	{
	}

	void StateMachine::AddState(StateRef newState, bool isReplacing)
	{
		this->_isAdding = true;							//set the flag to mode add of state
		this->_isReplacing = isReplacing;				//set priority of the added state

		this->_newState = std::move(newState);			//move pointer of current state
	}

	void StateMachine::RemoveState()
	{
		this->_isRemoving = true;						//set the flag to mode remove of state
	}

	void StateMachine::ProcessStateChange()
	{
		if (this->_isRemoving && !this->_states.empty())					//if flag of removing is active and stack of states not empty then
		{
			this->_states.pop();									//extract the current state from top of stack

			if (!this->_states.empty())										//if stack of states mot empty then
			{
				this->_states.top()->Resume();						//resume current state in the top of stack
			}

			this->_isRemoving = false;								//reset the flag of mode remove of state
		}

		if (this->_isAdding)												//or if state of adding is active then
		{
			if (!this->_states.empty())										//if stack of states not empty then
			{
				if (this->_isReplacing)										//if flag of replacing is active then
				{
					this->_states.pop();							//extract the previous state from top of stack
				}	
				else
				{
					this->_states.top()->Pause();					//else pause previous state
				}
			}
			
			this->_states.push(std::move(this->_newState));			//move current state to top of stack
			this->_states.top()->Init();							//initialize state in top of stack
			this->_isAdding = false;								//reset the flag of adding of state
		}
	}

	StateRef& StateMachine::GetActiveState()
	{
		return this->_states.top();						//return the first state from top of stack
	}
}
