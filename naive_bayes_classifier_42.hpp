/*
 * naive_bayes_classifier.hpp
 *
 *  Created on: May 3, 2011
 *      Author: ethan
 */

#ifndef NAIVE_BAYES_CLASSIFIER_HPP_
#define NAIVE_BAYES_CLASSIFIER_HPP_


/**
 * Two-class naive Bayes classifier.
 */

#include "feature.hpp"
#include <vector>

using std::vector;

class NaiveBayesClassifier {

  /* "m_features" maintains a list of all the features we are considering
   * in this classifier.
   *
   * "m_classTotals" counts how many training examples we've seen for each
   * of the three classes (0,1, and 2).
   */
protected:
  vector<Feature> m_features;
  int m_classTotals[3];

  //Compute and return the prior probability that a string belongs to a class
  //P(C=classNumber)
  double getPriorProbability(int classNumber) {
    double instancesOfClass = m_classTotals[classNumber];
    double totalInstancesSeen = m_classTotals[0] + m_classTotals[1] + m_classTotals[2];


    return instancesOfClass/totalInstancesSeen; 
  }

  //Compute and return the likelihood of the class, given the features.
  //This is P(F1=f1 and F2=f2 and ... Fn=fn | C=classNumber)
  //where f1, f2, ..., fn are 0 or 1 depending on the presence or absence
  //of the feature in that string.
  double getLikelihood(int classNumber, string s)
  {
    int featurePresent = m_features[0].isFeaturePresent(s);
    double probOfFeature = 
      m_features[0].getProbOfFeatureGivenClass(featurePresent, classNumber);

    //Uses independence assumption and computes:
    //probOfFeature = P(F1=f1|C=classNumber)P(F2=f2|C=classNumber)...P(Fn=fn|C=classNumber)
    for (size_t i = 1; i < m_features.size(); ++i){
      featurePresent = m_features[i].isFeaturePresent(s);
      probOfFeature *= m_features[i].getProbOfFeatureGivenClass(featurePresent, classNumber); 
    }

    return probOfFeature;
  }

public:
  //Create the set of features that we'll use.
  //For part 1 of the assignment, there are 26 features:
  //one for each letter of the alphabet.  So, you need to
  //create each feature and add it to m_features.
  NaiveBayesClassifier() {

    m_classTotals[0] = 0;  // initialize m_classTotals to 0;
    m_classTotals[1] = 0;
    m_classTotals[2] = 0;

    const int ALPHABET_CHARACTERS = 26;
    const int ASCII_UPPER_CASE = 65;

    for (int i = 0; i < ALPHABET_CHARACTERS; ++i){
      char upperCaseLetter = i + ASCII_UPPER_CASE;
      Feature newFeature(string(1, upperCaseLetter));
      m_features.push_back(newFeature);
    }
  }

  //Given a string and its correct classification, update:
  //(1) the counts that are used to compute the likelihoods.
  //Feature.addTrainingExample(featureVal, classNumber) should take care of this,
  //but you need to determine whether the feature is present for each feature.
  //(2) the counts that are used to compute the prior probability
  void addTrainingExample(string s, int classNumber){
    int featurePresent;

    for (size_t i = 0; i < m_features.size(); ++i){
      featurePresent = m_features[i].isFeaturePresent(s);
      m_features[i].addTrainingExample(featurePresent, classNumber);
    }

    m_classTotals[classNumber]++;
  }
  //Find Max{P(C=0) * ((for all j)P(Fj = fj | 0)), P(C=1) * ((for all j)P(Fj = fj | 1))}
  //Compute and return the most probable class (0 or 1) that this string
  //belongs to, using the maximum a posteriori (MAP) decision rule.
  //You can do this using calls to getPriorProbability and getLikelihood.
  //You do not need to call getPosteriorProbability.
  int classify(string s) {
    //Find P(C=0) * (for all j)P(Fj = fj | 0)
    double priorProbOfZero = getPriorProbability(0);
    double likelihoodOfZero = getLikelihood(0, s); 
    double mapProbOfZero = priorProbOfZero * likelihoodOfZero;

    double priorProbOfOne = getPriorProbability(1);
    double likelihoodOfOne = getLikelihood(1, s);
    double mapProbOfOne = priorProbOfOne * likelihoodOfOne;

    double priorProbOfTwo = getPriorProbability(2);
    double likelihoodOfTwo = getLikelihood(2, s);
    double mapProbOfTwo = priorProbOfTwo * likelihoodOfTwo;

    if (mapProbOfZero >= mapProbOfOne && mapProbOfZero >= mapProbOfTwo){
      return 0;
    }    
    else if (mapProbOfOne >= mapProbOfZero && mapProbOfOne >= mapProbOfTwo){
      return 1;
    }
    else{
      return 2;
    }  
  }

  //Compute and return the probability that the given string belongs to
  //class classNumber.
  //This is P(C=classNumber | F1=f1 and F2=f2 and ... Fn=fn)
  //where f1, f2, ..., fn are 0 or 1 depending on the presence or absence
  //of the feature in that string.
  //The code will be similar to classify, except that you need to also
  //need to use Bayes' rule and the law of total probability.
  //Note that this function is not necessary for a working classifier!
  //That is, you don't need to call getPosteriorProbability inside of classify.
  double getPosteriorProbability(int classNumber, string s)
  {
    //Numerator: P(F1 = f1 AND F2 = f2 AND .... AND Fn = fn | C=classNum)P(C = classNum)
    double numerator = getLikelihood(classNumber, s) * getPriorProbability(classNumber);
    //Denominator: P(F1 = ..... | C=0)P(C=0) + P(F1 = ..... | C=1)P(C=1) + P(F1 = ... | C=2)P(C=2)
    double denominator = (getLikelihood(0, s) * getPriorProbability(0))
                       + (getLikelihood(1, s) * getPriorProbability(1))  
                       + (getLikelihood(2, s) * getPriorProbability(2));

    return numerator/denominator;  
  }

};

#endif /* NAIVE_BAYES_CLASSIFIER_HPP_ */
