#include <iostream>
#include <thread>
#include "windows.h"
#include <conio.h>
#include <stdio.h>
#include <mutex>
using namespace std;

struct letter
    {
    int symbol;
    letter* link_front;
    letter* link_back;
    };
typedef letter *Pletter;

template <typename new_type> class lister
    {
    private:
        Pletter link_back;
        Pletter link_front;

    public:
        std::mutex locker;

        lister ()
            {
            link_back = new letter;
            link_front = new letter;

            link_back -> link_back = nullptr;
            link_back -> link_front = link_front;
            link_front -> link_back = link_back;
            link_front -> link_front = nullptr;

            std::cout << "created" << std::endl;
            }

        ~lister ()
            {
            std::cout << "deleted" << std::endl;
            }

        bool push_Back (new_type value)
            {
            std::cout << "puB_try" << std::endl;

            locker.lock ();

            Pletter link_tmp = new letter;

            link_back -> link_back = link_tmp;

            link_tmp -> link_back = nullptr;

            link_tmp -> link_front = link_back;

            link_back = link_tmp;

            link_back -> symbol = (int)value;

            link_tmp = nullptr;

            delete link_tmp;

            locker.unlock ();

            return true;
            }

        bool push_Front (new_type value)
            {
            std::cout << "puF_try" << std::endl;

            locker.lock ();

            Pletter link_tmp = new letter;

            link_front -> link_front = link_tmp;

            link_tmp -> link_front = nullptr;

            link_tmp -> link_back = link_front;

            //link_front = link_front -> link_front;

            link_front = link_tmp;

            link_front -> symbol = (int)value;

            link_tmp = nullptr;

            delete link_tmp;

            locker.unlock ();

            return true;
            }

        bool pop_Back ()
            {
            std::cout << "poB_try" << std::endl;

            locker.lock ();

            if (link_back -> link_front != link_front)
                {
                Pletter link_tmp = link_back;

                link_back -> link_front -> link_back = nullptr;

                link_back = link_back -> link_front;

                delete link_tmp;

                locker.unlock ();

                return true;
                }
            else
                {
                std::cout << "pop_back_false";

                locker.unlock ();

                return false;
                }
            }

        bool pop_Front ()
            {
            std::cout << "poF_try" << std::endl;

            locker.lock ();

            if (link_back -> link_front != link_front)
                {
                Pletter link_tmp = link_front;

                link_front -> link_back -> link_front = nullptr;

                link_front = link_front -> link_back;

                delete link_tmp;

                locker.unlock ();

                return true;
                }
            else
                {
                locker.unlock ();

                return false;
                }
            }

        int ret_Back ()
            {
            std::cout << "rB_try" << std::endl;

            return (int) link_back -> symbol;
            }

        int ret_Front ()
            {
            std::cout << "rf_try" << std::endl;

            return (int) link_front -> symbol;
            }

        bool check_end ()
            {
            if (link_back -> link_front == link_front)
                {
                std::cout << "true";

                Sleep (50);

                return true;
                }
            else
                {
                std::cout << "false";

                return false;
                }
            }
    };
