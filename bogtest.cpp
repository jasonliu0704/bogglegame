/******************************************************
* Tester for PA4 written by Ryan Bridges
* CSE 100 Fall 2014
* ****************************************************/

#include "baseboggleplayer.h"
#include "boggleplayer.h"
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <fstream>
#include <cstdio>
#include <ctime>

using namespace std;

int main(int argc, char *argv[])
{
    BogglePlayer *player = new BogglePlayer();

    set<string> validWords;
    string testString;
    set<string> lex;
    vector<int> positions;
    bool failed = false;


    string row0[] = {"A", "B", "C", "IN", "U"};
    string row1[] = {"M", "QEW", "NG", "J", "K"};
    string row2[] = {"XD", "FFA", "NNS", "KIP", "ZCF"};
    string row3[] = {"B", "WA", "RW", "H", "SR"};
    string row4[] = {"V", "S", "RQ", "W", "G"};
    string row5[] = {"MJK", "KH", "ER", "NJM", "H"};
    string row6[] = {"FW", "SDE", "D", "XZV", "JN"};
    string row7[] = {"UY", "FHB", "A", "XFG", "MB"};
    string row8[] = {"I", "QG", "XA", "CZ", "VC"};

    string *diceArray[] = {row0, row1, row2, row3, row4, row5, row6, row7, row8};

    lex.insert("abqewngjk");
    lex.insert("fhbadxzv");
    lex.insert("czvcmbjnh");
    lex.insert("iuyfw");
    lex.insert("rqwgnjm");
    lex.insert("nnskipsrg");
    lex.insert("doesNotExistZ");
    lex.insert("doesNotExistX");

    player->setBoard(9, 5, diceArray);

    for (short r = 0; r < 9; r++)
    {
        for (short c = 0; c < 5; c++)
        {
            testString.append(diceArray[r][c]);
            positions.push_back(r*5 + c);
        }
        // lex.insert(testString);
        if (player->isOnBoard(testString) != positions)
        {
            cout << "ERROR: isOnBoard failed for " << testString << endl;
            failed = true;
        }

        positions.clear();
        testString.clear();
    }

    player->buildLexicon(lex);
    if (!player->getAllValidWords(0, &validWords))
    {
        cout << "ERROR: getAllValidWords returned false when it should not have" << endl;
        failed = true;
    }
    for (auto &zod : validWords)
    {
        if (lex.find(zod) == lex.end())
        {
            cout << "ERROR: " << zod << " was in the set returned by getAllValidWords but not in the lexicon." << endl;
            failed = true;
        }
    }

    if (validWords.size() != (lex.size()-2))
    {
        cout << "ERROR: getAllValidWords did not did return a set with the correct number of words in it" << endl;
        failed = true;
    }
    validWords.clear();
    lex.clear();
    // 1x1 TEST //

    string rowQ[] = {"A"};
    string *diceArray2[] = {rowQ};
    player->setBoard(1, 1, diceArray2);
    vector<int> empty;
    testString = "A";
    positions.clear();
    positions.push_back(0);
    if (player->isOnBoard(testString) != positions)
    {
        cout << "ERROR: \"A\" was not in the right place on the board in the 1x1 test " << endl;
        failed = true;
    }
    if (player->isOnBoard("test") != empty)
    {
        cout << "ERROR: The 1x1 board found a word that does not exist on the board " << endl;
        failed = true;
    }

    // Default Tests //

    string wordA("a");
    string wordX("x");
    lex.insert(wordA);
    lex.insert("z");
    string rowF[] = {"D","C"};
    string rowG[] = {"b","A"};
    string *diceArray3[] = {rowF,rowG};

    player->buildLexicon(lex);

    player->setBoard(2,2,diceArray3);

    if (player->isInLexicon(wordX))
    {
        std::cerr << "Apparent problem with isInLexicon #1." << std::endl;
        failed = true;;
    }
    if (!player->isInLexicon(wordA))
    {
        std::cerr << "Apparent problem with isInLexicon #2." << std::endl;
        failed = true;;
    }

    if (player->isOnBoard(wordX).size() > 0)
    {
        std::cerr << "Apparent problem with isOnBoard #1." << std::endl;
        failed = true;;
    }

    positions.clear();
    positions = player->isOnBoard(wordA);
    if (positions.size() != 1 || positions[0] != 3)
    {
        std::cerr << "Apparent problem with isOnBoard #2." << std::endl;
        failed = true;;
    }


    if (!player->getAllValidWords(0,&validWords))
    {
        std::cerr << "Apparent problem with getAllValidWords #1." << std::endl;
        failed = true;;
    };
    if (validWords.size() != 1 || validWords.count(wordA) != 1)
    {
        cout << lex.size() << endl;
        cout << lex.count(wordA) << endl;
        std::cerr << "Apparent problem with getAllValidWords #2." << std::endl;
        failed = true;;
    }
    positions.clear();
    validWords.clear();
    lex.clear();

    // Is on board test. Could be written a lot better.
    // But it's just a hacked together test
    string row01[] = {"T","H","L","I"};
    string row11[] = {"R","E","A","D"};
    string row21[] = {"I","L","M","O"};
    string row31[] = {"F","P","S","N"};
    string *board[] = {row01,row11,row21,row31};

    player->setBoard(4,4,board);
    std::vector<int>checkVector;
    std::vector<int>checkVector2;
    std::vector<int>checkVector3;

    checkVector = player->isOnBoard("TRIP");
    checkVector2.push_back(0);
    checkVector2.push_back(4);
    checkVector2.push_back(8);
    checkVector2.push_back(13);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: TRIP was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    checkVector = player->isOnBoard("mad");
    checkVector2.push_back(10);
    checkVector2.push_back(6);
    checkVector2.push_back(7);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: mad was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    checkVector = player->isOnBoard("Help");
    checkVector2.push_back(1);
    checkVector2.push_back(5);
    checkVector2.push_back(9);
    checkVector2.push_back(13);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: Help was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    checkVector = player->isOnBoard("lamE");
    checkVector2.push_back(2);
    checkVector2.push_back(6);
    checkVector2.push_back(10);
    checkVector2.push_back(5);

    checkVector3.push_back(9);
    checkVector3.push_back(6);
    checkVector3.push_back(10);
    checkVector3.push_back(5);

    if (checkVector != checkVector2 && checkVector != checkVector3)
    {
        cout << "ERROR: lamE was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();
    checkVector3.clear();

    checkVector = player->isOnBoard("dOmE");
    checkVector2.push_back(7);
    checkVector2.push_back(11);
    checkVector2.push_back(10);
    checkVector2.push_back(5);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: dOmE was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    checkVector = player->isOnBoard("FiRe");
    checkVector2.push_back(12);
    checkVector2.push_back(8);
    checkVector2.push_back(4);
    checkVector2.push_back(5);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: FiRe was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    checkVector = player->isOnBoard("flip");
    checkVector2.push_back(12);
    checkVector2.push_back(9);
    checkVector2.push_back(8);
    checkVector2.push_back(13);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: flip was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    checkVector = player->isOnBoard("real");
    checkVector2.push_back(4);
    checkVector2.push_back(5);
    checkVector2.push_back(6);
    checkVector2.push_back(2);

    checkVector3.push_back(4);
    checkVector3.push_back(5);
    checkVector3.push_back(6);
    checkVector3.push_back(9);
    if (checkVector != checkVector2 && checkVector != checkVector3)
    {
        cout << "ERROR: real was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();
    checkVector3.clear();

    checkVector = player->isOnBoard("ream");
    checkVector2.push_back(4);
    checkVector2.push_back(5);
    checkVector2.push_back(6);
    checkVector2.push_back(10);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: ream was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    checkVector = player->isOnBoard("HEAL");
    checkVector2.push_back(1);
    checkVector2.push_back(5);
    checkVector2.push_back(6);
    checkVector2.push_back(2);

    checkVector3.push_back(1);
    checkVector3.push_back(5);
    checkVector3.push_back(6);
    checkVector3.push_back(9);
    if (checkVector != checkVector2 && checkVector != checkVector3)
    {
        cout << "ERROR: HEAL was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();
    checkVector3.clear();

    checkVector = player->isOnBoard("had");
    checkVector2.push_back(1);
    checkVector2.push_back(6);
    checkVector2.push_back(7);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: had was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    checkVector = player->isOnBoard("hAm");
    checkVector2.push_back(1);
    checkVector2.push_back(6);
    checkVector2.push_back(10);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: hAm was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    checkVector = player->isOnBoard("son");
    checkVector2.push_back(14);
    checkVector2.push_back(11);
    checkVector2.push_back(15);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: son was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    checkVector = player->isOnBoard("LID");
    checkVector2.push_back(2);
    checkVector2.push_back(3);
    checkVector2.push_back(7);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: LID was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    checkVector = player->isOnBoard("dame");
    checkVector2.push_back(7);
    checkVector2.push_back(6);
    checkVector2.push_back(10);
    checkVector2.push_back(5);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: dame was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    checkVector = player->isOnBoard("team");
    checkVector2.push_back(0);
    checkVector2.push_back(5);
    checkVector2.push_back(6);
    checkVector2.push_back(10);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: team was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    // Corner Test Case
    string row04[] = {"c", "a", "X", "X", "X"};
    string row14[] = {"r", "t", "X", "X", "X"};
    string row24[] = {"X", "X", "X", "X", "X"};
    string row34[] = {"X", "X", "X", "X", "X"};
    string row44[] = {"X", "X", "X", "X", "X"};
    string row54[] = {"X", "X", "X", "X", "X"};

    string *diceArray4[] = {row04, row14, row24, row34, row44, row54};

    lex.insert("cart");
    lex.insert("car");
    lex.insert("cat");
    lex.insert("arc");
    lex.insert("art");
    lex.insert("at");
    lex.insert("a");
    lex.insert("act");
    lex.insert("tar");
    lex.insert("rat");

    player->buildLexicon(lex);
    player->setBoard(6, 5, diceArray4);

    for (auto &zod : lex)
    {
        if (!player->isInLexicon(zod))
        {
            cerr << "ERROR: " << zod << " was not found in the Lexicon" << endl;
            failed = true;
        }
    }

    if (!player->getAllValidWords(1, &validWords))
    {
        cerr << "ERROR: getAllValidWords returned false when it should not have" << endl;
        failed = true;
    }

    if (validWords.size() != lex.size())
    {
        cerr << "ERROR: getAllValidWords did not did return a set with the correct number of words in it" << endl;
        failed = true;
    }

    for (auto &zod : lex)
    {
        if (validWords.find(zod) == validWords.end())
        {
            cerr << "ERROR: " << zod << " was in the lexicon and on the board but was not found by getAllValidWords" << endl;
            failed = true;
        }
    }

    validWords.clear();
    lex.clear();

    checkVector = player->isOnBoard("CART");
    checkVector2.push_back(0);
    checkVector2.push_back(1);
    checkVector2.push_back(5);
    checkVector2.push_back(6);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: CART was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    checkVector = player->isOnBoard("CAR");
    checkVector2.push_back(0);
    checkVector2.push_back(1);
    checkVector2.push_back(5);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: CAR was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    checkVector = player->isOnBoard("CAT");
    checkVector2.push_back(0);
    checkVector2.push_back(1);
    checkVector2.push_back(6);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: CAT was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    checkVector = player->isOnBoard("ARC");
    checkVector2.push_back(1);
    checkVector2.push_back(5);
    checkVector2.push_back(0);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: ARC was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    checkVector = player->isOnBoard("ART");
    checkVector2.push_back(1);
    checkVector2.push_back(5);
    checkVector2.push_back(6);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: ART was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    checkVector = player->isOnBoard("AT");
    checkVector2.push_back(1);
    checkVector2.push_back(6);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: AT was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    checkVector = player->isOnBoard("A");
    checkVector2.push_back(1);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: A was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    checkVector = player->isOnBoard("ACT");
    checkVector2.push_back(1);
    checkVector2.push_back(0);
    checkVector2.push_back(6);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: ACT was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    checkVector = player->isOnBoard("TAR");
    checkVector2.push_back(6);
    checkVector2.push_back(1);
    checkVector2.push_back(5);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: TAR was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    checkVector = player->isOnBoard("RAT");
    checkVector2.push_back(5);
    checkVector2.push_back(1);
    checkVector2.push_back(6);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: RAT was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    std::ifstream in("lex.txt");

    // Load the lexicon from file
    string word;
    set<string> results;
    while (std::getline(in, word))
        lex.insert(word);
    in.close();

    // setup the board
    int rows;
    int cols;
    in.open("brd.txt");
    in >> rows;
    in >> cols;
    std::string **brd = new std::string*[rows];

    for (int i = 0; i < rows; ++i)
    {
        std::string *row6 = new std::string[cols];

        for (int j = 0; j < cols; ++j)
        {
            in >> row6[j];
        }
        brd[i] = row6;
    }

    in.close();

    // Store results into a set so we can compare it to what getAllValidWords() returns
    in.open("results.txt");
    while (std::getline(in, word))
        results.insert(word);
    in.close();

    player->buildLexicon(lex);
    player->setBoard(rows, cols, brd);

    clock_t start;
    double duration;
    start = clock();
    player->getAllValidWords(2, &validWords);
    duration = (clock() - start) / (double) CLOCKS_PER_SEC;

    cout << "Your implementation of getAllValidWords took " << duration << " seconds to find all 5450 words" << endl;

    if (!(duration < 10))
    {
        cout << "ERROR: getAllValidWords was not completed in under 10 seconds" << endl;
        failed = true;
    }

    if (!(duration < 5))
    {
        cout << "ERROR: getAllValidWords was not completed in under 5 seconds" << endl;
        failed = true;
    }

    if (validWords.size() != results.size())
    {
        cout << "ERROR: getAllValidWords did not find the correct number of words" << endl;
        failed = true;
    }

    for (auto zod : results)
    {
        if (validWords.find(zod) == validWords.end())
        {
            cout << "ERROR: " << zod << " was not found in getAllValidWords when it should have been" << endl;
            failed = true;
        }
    }

    lex.clear();   
    in.open("boglex.txt");
    // Load the lexicon from file

    while (std::getline(in, word))
        lex.insert(word);
    in.close();

    player->buildLexicon(lex);
    player->setBoard(rows, cols, brd);
    validWords.clear();
    start = clock();
    player->getAllValidWords(2, &validWords); 

    cout << validWords.size() << endl;

    if (failed)
        cout << "FAILURE! At least one test did not pass. " << endl;
    else
        cout << "SUCCESS! All tests passed. " << endl;

    for (int zod = 0; zod < rows; ++zod) {
        delete[] brd[zod];
        brd[zod] = NULL;
    }
    delete[] brd;
    brd = NULL;
   
    delete player;
    player = NULL;

    return 0;
}
