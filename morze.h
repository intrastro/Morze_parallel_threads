#include "lister2.h"

const int DOT     = 20;
const int DASH    = 50;
const int SILENCE = 100;
const int LONG_SILENCE = 200;

class morze
    {
    public:

        std::mutex locker;

        lister <int> new_list;

        morze ()
            {
            std::cout << "morze creation" << std::endl;

            Beep (600, 1500);

            start_morze ();
            }

        ~morze ()
            {
            }

        void start_morze ()
            {
            auto writing = std::thread ([this] {this -> writing (std::ref (new_list));});

            writing.detach ();

            auto beeping = std::thread ([this] {this -> beeping (std::ref (new_list));});

            beeping.detach ();
            }


        void writing (lister <int> &new_list)
            {
            char symbol = '\0';

            while (1)
                {
                new_list.clearance_true ();

                symbol = getch ();

                std::cout << "OK_getting" << std::endl;

                locker.lock ();

                translator ((int) symbol);

                Sleep (50);

                new_list.push_Front (LONG_SILENCE);

                locker.unlock ();
                }
            }

         void beeping (lister <int> &new_list)
            {
            Sleep (10000);

            std::cout << "!!!" << std::endl;

            while (1)
                {
                locker.lock ();

                if (new_list.check_end () == FALSE)
                    {
                    if (new_list.ret_Back () == SILENCE)
                        {
                        Beep (50, 200);
                        }
                    else if (new_list.ret_Back () == DOT)
                        {
                        Beep (700, 100);
                        }
                    else if (new_list.ret_Back () == DASH)
                        {
                        Beep (700, 500);
                        }
                    else if (new_list.ret_Back () == LONG_SILENCE)
                        {
                        Beep (100, 500);
                        }
                    else
                        {
                        ;
                        }

                    if (new_list.pop_Back ())
                        {
                        std::cout << "OK_beep" << std::endl;
                        }

                    Sleep (50);
                    }
                else
                    {
                    new_list.clearance_false ();

                    new_list.clear_list_to_front ();

                    new_list.clearance_true ();
                    }

                locker.unlock ();
                }
            }

         void translator (int symbol)
            {
            switch (symbol)
                {
                case 'A':
                    {
                    new_list.push_Front (DOT);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DASH);

                    break;
                    }
                case 'B':
                    {
                    new_list.push_Front (DASH);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DOT);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DOT);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DOT);

                    break;
                    }
                case 'C':
                    {

                    new_list.push_Front (DASH);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DOT);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DASH);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DOT);

                    break;
                    }
                case 'D':
                    {

                    new_list.push_Front (DASH);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DOT);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DOT);

                    break;
                    }
                case 'E':
                    {
                    new_list.push_Front (DOT);

                    break;
                    }
                case 'F':
                    {
                    new_list.push_Front (DOT);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DOT);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DASH);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DOT);

                    break;
                    }
                case 'G':
                    {
                    new_list.push_Front (DASH);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DASH);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DOT);

                    break;
                    }
                case 'H':
                    {
                    new_list.push_Front (DOT);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DOT);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DOT);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DOT);

                    break;
                    }
                case 'I':
                    {
                    new_list.push_Front (DOT);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DOT);

                    break;
                    }
                case 'J':
                    {
                    new_list.push_Front (DOT);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DASH);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DASH);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DASH);

                    break;
                    }
                case 'K':
                    {
                    new_list.push_Front (DASH);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DOT);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DASH);

                    break;
                    }
                case 'L':
                    {
                    new_list.push_Front (DOT);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DASH);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DOT);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DOT);

                    break;
                    }
                case 'M':
                    {
                    new_list.push_Front (DASH);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DASH);

                    break;
                    }
                case 'N':
                    {
                    new_list.push_Front (DASH);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DOT);

                    break;
                    }
                case 'O':
                    {
                    new_list.push_Front (DASH);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DASH);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DASH);

                    break;
                    }
                case 'P':
                    {
                    new_list.push_Front (DOT);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DASH);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DASH);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DOT);

                    break;
                    }
                case 'Q':
                    {
                    new_list.push_Front (DASH);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DASH);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DOT);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DASH);

                    break;
                    }
                case 'R':
                    {
                    new_list.push_Front (DOT);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DASH);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DOT);

                    break;
                    }
                case 'S':
                    {
                    new_list.push_Front (DOT);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DOT);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DOT);

                    break;
                    }
                case 'T':
                    {
                    new_list.push_Front (DASH);

                    break;
                    }
                case 'U':
                    {
                    new_list.push_Front (DOT);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DOT);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DASH);

                    break;
                    }
                case 'V':
                    {
                    new_list.push_Front (DOT);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DOT);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DOT);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DASH);

                    break;
                    }
                case 'W':
                    {
                    new_list.push_Front (DOT);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DASH);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DASH);

                    break;
                    }
                case 'X':
                    {
                    new_list.push_Front (DASH);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DOT);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DOT);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DASH);

                    break;
                    }
                case 'Y':
                    {
                    new_list.push_Front (DASH);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DOT);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DASH);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DASH);

                    break;
                    }
                case 'Z':
                    {
                    new_list.push_Front (DASH);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DASH);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DOT);

                    new_list.push_Front (SILENCE);

                    new_list.push_Front (DOT);

                    break;
                    }
                case ' ':
                    {
                    new_list.push_Front (SILENCE);

                    new_list.push_Front (SILENCE);

                    new_list.push_Back (SILENCE);

                    new_list.push_Back (SILENCE);

                    break;
                    }

                default:
                    {
                    break;
                    }
                }
            }
    };
