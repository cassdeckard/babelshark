// $Id $

#include "Subject.h"

namespace BabelShark
{
    void Subject::Attach(Observer* observer)
    {
        _Observers.push_back(observer);
    }

    void Subject::Detach(Observer* observer)
    {
        _Observers.remove(observer);
    }

    void Subject::Notify()
    {
        for ( std::list<Observer*>::iterator it = _Observers.begin(); it != _Observers.end(); it++ )
        {
            (*it)->Update(this);
        }
    }

}
