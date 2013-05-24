/*
 * Singleton.h
 *
 *  Created on: 22.05.2013
 *      Author: nopper
 */

#ifndef SINGLETON_H_
#define SINGLETON_H_

template<class S>
class Singleton
{

	private:

		static S* instance;

	protected:

		Singleton()
		{
		}

		virtual ~Singleton()
		{
		}

	public:

		static S* getInstance()
		{
			if (!instance)
			{
				instance = new S();
			}

			return instance;
		}

		static void terminate()
		{
			if (instance)
			{
				delete instance;

				instance = nullptr;
			}
		}

};

template<class S>
S* Singleton<S>::instance = nullptr;

#endif /* SINGLETON_H_ */
