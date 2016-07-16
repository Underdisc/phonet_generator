/*****************************************************************************/
/*!
\file Phonet.cpp
\author Connor Deakin
\par E-mail: connortdeakin\@gmail.com
\par Project: PhonetGenerator
\date 27/06/2016
\brief
  Contains the implementation of the Phonet. Details on a Phonet's purpose can
  be found in the Phonet's header file.

\par
    Functions Include:
    - Default Constructor
    - Parameterized Constructor: 2
    - Destructor
    - generate
    - print_phonet
    - print_pronunciation
    - print_spelling
    - operator <<

\par Functions Undergoing Improvement
    - generate
*/
/*****************************************************************************/

#include "../header/Phonet.h" // Phonet:c

#include <cstdlib>  // srand, rand
#include <iostream> // cout, endl

/*****************************************************************************/
/*!
\brief
  Defualt constructor for the Phonet. A Phonet will start with a min length of
  2 and a max length of 10.
*/
/*****************************************************************************/
Phonet::Phonet() : m_phonemes(), m_min_length(2), m_max_length(10)
{
}

/*****************************************************************************/
/*!
\brief
  Parameterized Constructor. The Phonet will be generated during the
  object creation. The Phonet will begin with a min length of 2 and a max length
  of ten.

\param consonants
  A reference to the vector of consonant Phonmes being used for the Phonet.
\param vowels
  A reference to the vector of vowel Phonemes being used for the Phonet.
\param min_length
  The minimum length the Phonet could have when generated.
\param max_length
  The maximum length the Phonet could have when generated.
*/
/*****************************************************************************/
Phonet::Phonet(const std::vector<Phoneme> & consonants,
               const std::vector<Phoneme> & vowels,
               const size_t min_length, const size_t max_length):
m_min_length(min_length),
m_max_length(max_length)
{
  generate(consonants, vowels);
}

/*****************************************************************************/
/*!
\brief
  Parameterized constructor. Given a vector of Phonemes, a Phonet object will
  be created. The min and max lengths of the Phonet will be the size of the
  Phoneme vector.

\param phonemes
  The vector of strings containing the phonemes the Phonet will be initialized
  with.
*/
/*****************************************************************************/

Phonet::Phonet(const std::vector<Phoneme> & phonemes):
m_min_length(phonemes.size()),
m_max_length(phonemes.size())
{
  m_phonemes = phonemes;
}

/*****************************************************************************/
/*!
\brief
  Empty Phonet destructor.
*/
/*****************************************************************************/
Phonet::~Phonet()
{}

/*****************************************************************************/
/*!
\brief
  Given a vector of both consonant and vowel Phonemes and a seed, a randomized
  phonet will be generated with the rules of the English phonetic alphabet.
  This is currently pretty screwy.

\param consonants
  The Vector of consonant Phonemes being used for the generation.
\param vowels
  The vector of vowel Phonemes being used for the gneneration.
*/
/*****************************************************************************/

void Phonet::generate(const std::vector<Phoneme> & consonants,
                      const std::vector<Phoneme> & vowels)
{
  m_phonemes.clear();

  size_t length = (rand() % (m_max_length - m_min_length + 1)) + m_min_length;
  Phoneme_Type type = static_cast<Phoneme_Type>(rand() % 2);

  while(length)
  {
    if(type)
    {
      size_t vowel_index = rand() % vowels.size();
      m_phonemes.push_back(vowels[vowel_index]);
      type = static_cast<Phoneme_Type>(0);

    }
    else
    {
      size_t consonant_index = rand() % consonants.size();
      m_phonemes.push_back(consonants[consonant_index]);
      type = static_cast<Phoneme_Type>(1);
    }
    --length;
  }
}

/*****************************************************************************/
/*!
\brief
  Prints out the Phonemes in the constructed Phonet to console.
*/
/*****************************************************************************/
void Phonet::print_phonet() const
{
  std::vector<Phoneme>::const_iterator phoneme;
  phoneme = m_phonemes.begin();
  if(phoneme != m_phonemes.end())
  {
    std::cout << *phoneme;
    while(true)
    {
      ++phoneme;
      if(phoneme == m_phonemes.end())
        break;
      std::cout << ":" << *phoneme;
    }
  }
}

/*****************************************************************************/
/*!
\brief
  Prints out an example of how the Phonet is supposed to be pronounced to
  console. The example will consist of multiple words printed in the correct
  order. Each word will consist of one Phoneme that is in the word generated.
*/
/*****************************************************************************/
void Phonet::print_pronunciation() const
{
  std::vector<Phoneme>::const_iterator phoneme;
  phoneme = m_phonemes.begin();
  if(phoneme != m_phonemes.end())
  {
    (*phoneme).print_pronunciation();
    while(true)
    {
      ++phoneme;
      if(phoneme == m_phonemes.end())
        break;
      std::cout << " : ";
      (*phoneme).print_pronunciation();
    }
  }
}

/*****************************************************************************/
/*!
\brief
  Prints a possible random spelling for the Phonet.
*/
/*****************************************************************************/
void Phonet::print_spelling() const
{
  std::vector<Phoneme>::const_iterator phoneme;
  for(phoneme = m_phonemes.begin(); phoneme != m_phonemes.end(); ++phoneme)
    (*phoneme).print_spelling();
}

/*****************************************************************************/
/*!
\brief
  Overloads the output operator to print a Phonet to console. Only the Phonet
  itself will be printed, not the pronunciation or suggested spellings.

\param os
  The ostream the phonet will be sent to.
\param rhs
  The Phonet that is being sent to the ostream.

\return The ostream the Phonet was sent to.
*/
/*****************************************************************************/
std::ostream & operator<<(std::ostream & os, const Phonet & rhs)
{
  rhs.print_phonet();
  return os;
}
