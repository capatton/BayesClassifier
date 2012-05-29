/*
 * feature.hpp
 *
 *  Created on: May 3, 2011
 *      Author: Ethan L. Schreiber
 *      Adapted from java code written by Andrew McGregor
 */

#ifndef FEATURE_HPP_
#define FEATURE_HPP_

#include <string>
#include <cstring>

 using std::string;
/**
 * feature.hpp
 *
 * Stores counts and computes probabilities for one boolean feature.
 */
class Feature {

  /* counts[][] is a 2x2 matrix that stores for each of the
   * 2 classes (0 and 1), the number of training examples we've
   * seen that don't have the feature (0) or have it (1).
   *
   * So counts[0][0] would be the number of training examples that fall
   * into class 0, that don't have the feature.
   *
   * totalPerClass[] stores the number of training examples we've seen
   * per class.  So totalPerClass[i] should always equal
   * counts[i][0] + counts[i][1].
   */

protected:
  //Added another class to m_counts and m_totalPerClass
  int m_counts[3][2]; //m_counts[classNum][featurePresent]
  int m_totalPerClass[3]; //m_counts[classNum][0] + m_counts[classNum][1]
  string m_toMatch;
public:
  Feature(string toMatch) : m_toMatch(toMatch) {
    m_counts[0][0] = 0;
    m_counts[0][1] = 0;
    m_counts[1][0] = 0;
    m_counts[1][1] = 0;
    m_counts[2][0] = 0;
    m_counts[2][1] = 0;

    m_totalPerClass[0] = 0;
    m_totalPerClass[1] = 0;
    m_totalPerClass[2] = 0;
  }

  
  //Determine whether this feature occurs in the string.
  //Return 1 if the feature is present; 0 otherwise.
  int isFeaturePresent(string s) {
    if (std::string::npos != s.find(m_toMatch)){
      return 1;
    }

    return 0; 
  }

  // Given the absence/presence of this feature for the given class,
  // update the counts used to compute the probabilities.
  // classNumber = the number of the class for this example (0 or 1)
  // featurePresence = 0 or 1 stating the presence or absence of this feature
  void addTrainingExample(int featurePresence, int classNumber) {
     m_counts[classNumber][featurePresence]++;
     m_totalPerClass[classNumber]++;
  }

  //Return (# examples with featurePresence and classNumber (+ 1)/(# examples with classNumber (+ 3))
  double getProbOfFeatureGivenClass(int featurePresence, int classNumber) {
    int NUMERATOR_SMOOTHING = 1;
    int DENOMINATOR_SMOOTHING = 3;
    double numerator = m_counts[classNumber][featurePresence] + NUMERATOR_SMOOTHING;
    double denominator = m_totalPerClass[classNumber] + DENOMINATOR_SMOOTHING;

    return numerator/denominator; 
  }
};

#endif /* FEATURE_HPP_ */
