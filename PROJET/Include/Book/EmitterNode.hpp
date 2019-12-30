#ifndef EMITTERNODE_HPP
#define EMITTERNODE_HPP

#include <Book/SceneNode.hpp>
#include <Book/Particle.hpp>


class ParticleNode;

class EmitterNode : public SceneNode
{
	public:
		explicit				EmitterNode(Particle::Type type);


	private:
		virtual void			updateCurrent(sf::Time dt, CommandQueue& commands);
		
		void					emitParticles(sf::Time dt);


	private:
		sf::Time				mAccumulatedTime;
		Particle::Type			mType;
		ParticleNode*			mParticleSystem;
};

#endif // EMITTERNODE_HPP
