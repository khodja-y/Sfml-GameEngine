#ifndef COMMANDQUEUE_HPP
#define COMMANDQUEUE_HPP

#include <Book/Command.hpp>

#include <queue>


class CommandQueue
{
	public:
									~CommandQueue();
		void						push(const Command& command);
		Command						pop();
		bool						isEmpty() const;

		
	private:
		std::queue<Command>			mQueue;
};

#endif // COMMANDQUEUE_HPP
