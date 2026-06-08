#pragma once
#include <cstring>

/**
 * A classification chain for tabular data
 */
namespace tinyml4all {
    /**
 * Handle all inputs of the chain
 * (from outside and internal)
 */
class Input {
    public:
        
            float _S0Owru__r;
        
            float _kutfua__b;
        
            float _svXR0N__g;
        

        /**
         * Copy from other input
         */
        void copyFrom(Input& other) {
            
                _S0Owru__r = other._S0Owru__r;
            
                _kutfua__b = other._kutfua__b;
            
                _svXR0N__g = other._svXR0N__g;
            
        }
};
    /**
 * Handle all outputs
 * TODO
 */
 class Output {
    public:
        struct {
            uint8_t idx;
            uint8_t prevIdx;
            float score;
            float prevScore;
            char label[32];
            char prevLabel[32];
        } classification;

        Output() {
            classification.idx = 0;
            classification.score = 0;
        }
 };

    // processing blocks
    
    /**
 * Scale(method=robust, offsets=[20.5 20.  16.5], scales=[ 9.25 13.25  7.25])
 */
class _aCm4WH__scale_8538129521428 {
    public:

        void operator()(Input& input, Output& output) {
            

            
                
                    input._S0Owru__r = (input._S0Owru__r - 20.5f) * 0.10810810810810811f;
                
                    input._svXR0N__g = (input._svXR0N__g - 20.0f) * 0.07547169811320754f;
                
                    input._kutfua__b = (input._kutfua__b - 16.5f) * 0.13793103448275862f;
                
            

            
        }

        /**
         * Always ready
         */
        bool isReady() {
            return true;
        }
};
    
    /**
 * DecisionTreeClassifier(max_depth=10, max_features='sqrt', min_samples_leaf=5,
                       random_state=425403995)
 */
class _xCKXbE__decisiontree_8538128331201 {
    public:

        void operator()(Input& input, Output& output) {
            
                
    if (input._svXR0N__g < -0.4150943458080292f) {
        
    if (input._svXR0N__g < -0.7924528419971466f) {
        
    output.classification.idx = 2;
    output.classification.score = 0.30833333333333335;
    return;

    }
    else {
        
    if (input._S0Owru__r < -1.1891891956329346f) {
        
    output.classification.idx = 1;
    output.classification.score = 0.225;
    return;

    }
    else {
        
    output.classification.idx = 2;
    output.classification.score = 0.30833333333333335;
    return;

    }

    }

    }
    else {
        
    if (input._svXR0N__g < 0.18867924809455872f) {
        
    if (input._kutfua__b < 0.13793103769421577f) {
        
    if (input._kutfua__b < -0.27586207538843155f) {
        
    output.classification.idx = 0;
    output.classification.score = 0.30833333333333335;
    return;

    }
    else {
        
    output.classification.idx = 0;
    output.classification.score = 0.30833333333333335;
    return;

    }

    }
    else {
        
    output.classification.idx = 0;
    output.classification.score = 0.30833333333333335;
    return;

    }

    }
    else {
        
    if (input._S0Owru__r < 0.10810810141265392f) {
        
    output.classification.idx = 1;
    output.classification.score = 0.225;
    return;

    }
    else {
        
    if (input._S0Owru__r < 0.7567567527294159f) {
        
    output.classification.idx = 3;
    output.classification.score = 0.15833333333333333;
    return;

    }
    else {
        
    if (input._kutfua__b < 0.8275862038135529f) {
        
    output.classification.idx = 3;
    output.classification.score = 0.15833333333333333;
    return;

    }
    else {
        
    if (input._svXR0N__g < 1.396226406097412f) {
        
    output.classification.idx = 0;
    output.classification.score = 0.30833333333333335;
    return;

    }
    else {
        
    output.classification.idx = 1;
    output.classification.score = 0.225;
    return;

    }

    }

    }

    }

    }

    }

            
        }

        bool isReady() {
            return true;
        }
};/**
 * DecisionTreeClassifier(max_depth=10, max_features='sqrt', min_samples_leaf=5,
                       random_state=1204120478)
 */
class _rOGxgn__decisiontree_8538128852318 {
    public:

        void operator()(Input& input, Output& output) {
            
                
    if (input._S0Owru__r < -0.10810810513794422f) {
        
    if (input._S0Owru__r < -0.9189189076423645f) {
        
    output.classification.idx = 1;
    output.classification.score = 0.2916666666666667;
    return;

    }
    else {
        
    if (input._S0Owru__r < -0.4324324429035187f) {
        
    output.classification.idx = 2;
    output.classification.score = 0.225;
    return;

    }
    else {
        
    if (input._S0Owru__r < -0.3243243247270584f) {
        
    output.classification.idx = 1;
    output.classification.score = 0.2916666666666667;
    return;

    }
    else {
        
    output.classification.idx = 2;
    output.classification.score = 0.225;
    return;

    }

    }

    }

    }
    else {
        
    if (input._kutfua__b < 1.6551724076271057f) {
        
    if (input._svXR0N__g < 0.03773584961891174f) {
        
    output.classification.idx = 0;
    output.classification.score = 0.2;
    return;

    }
    else {
        
    if (input._svXR0N__g < 0.5660377442836761f) {
        
    if (input._S0Owru__r < 0.5405405461788177f) {
        
    output.classification.idx = 3;
    output.classification.score = 0.2833333333333333;
    return;

    }
    else {
        
    if (input._svXR0N__g < 0.4150943458080292f) {
        
    output.classification.idx = 3;
    output.classification.score = 0.2833333333333333;
    return;

    }
    else {
        
    output.classification.idx = 3;
    output.classification.score = 0.2833333333333333;
    return;

    }

    }

    }
    else {
        
    output.classification.idx = 0;
    output.classification.score = 0.2;
    return;

    }

    }

    }
    else {
        
    output.classification.idx = 1;
    output.classification.score = 0.2916666666666667;
    return;

    }

    }

            
        }

        bool isReady() {
            return true;
        }
};/**
 * DecisionTreeClassifier(max_depth=10, max_features='sqrt', min_samples_leaf=5,
                       random_state=943786903)
 */
class _jvaidt__decisiontree_8538128852369 {
    public:

        void operator()(Input& input, Output& output) {
            
                
    if (input._S0Owru__r < 0.21621620655059814f) {
        
    if (input._kutfua__b < -0.41379310190677643f) {
        
    if (input._kutfua__b < -0.6896551549434662f) {
        
    if (input._svXR0N__g < -0.8679245412349701f) {
        
    output.classification.idx = 2;
    output.classification.score = 0.225;
    return;

    }
    else {
        
    output.classification.idx = 2;
    output.classification.score = 0.225;
    return;

    }

    }
    else {
        
    output.classification.idx = 2;
    output.classification.score = 0.225;
    return;

    }

    }
    else {
        
    if (input._svXR0N__g < -0.18867924809455872f) {
        
    output.classification.idx = 1;
    output.classification.score = 0.21666666666666667;
    return;

    }
    else {
        
    if (input._kutfua__b < 0.0f) {
        
    output.classification.idx = 0;
    output.classification.score = 0.20833333333333334;
    return;

    }
    else {
        
    output.classification.idx = 1;
    output.classification.score = 0.21666666666666667;
    return;

    }

    }

    }

    }
    else {
        
    if (input._kutfua__b < 0.8275861740112305f) {
        
    if (input._svXR0N__g < 0.18867924809455872f) {
        
    output.classification.idx = 3;
    output.classification.score = 0.35;
    return;

    }
    else {
        
    output.classification.idx = 3;
    output.classification.score = 0.35;
    return;

    }

    }
    else {
        
    if (input._svXR0N__g < 0.9433962404727936f) {
        
    output.classification.idx = 0;
    output.classification.score = 0.20833333333333334;
    return;

    }
    else {
        
    output.classification.idx = 1;
    output.classification.score = 0.21666666666666667;
    return;

    }

    }

    }

            
        }

        bool isReady() {
            return true;
        }
};/**
 * DecisionTreeClassifier(max_depth=10, max_features='sqrt', min_samples_leaf=5,
                       random_state=1469730873)
 */
class _xWGkvJ__decisiontree_8538128852774 {
    public:

        void operator()(Input& input, Output& output) {
            
                
    if (input._svXR0N__g < -0.4150943458080292f) {
        
    if (input._S0Owru__r < -1.2432432770729065f) {
        
    output.classification.idx = 1;
    output.classification.score = 0.225;
    return;

    }
    else {
        
    output.classification.idx = 2;
    output.classification.score = 0.31666666666666665;
    return;

    }

    }
    else {
        
    if (input._kutfua__b < 1.58620685338974f) {
        
    if (input._S0Owru__r < -0.2702702730894089f) {
        
    output.classification.idx = 1;
    output.classification.score = 0.225;
    return;

    }
    else {
        
    if (input._kutfua__b < 0.8275862038135529f) {
        
    if (input._S0Owru__r < 0.5405405461788177f) {
        
    if (input._kutfua__b < 0.0f) {
        
    output.classification.idx = 0;
    output.classification.score = 0.24166666666666667;
    return;

    }
    else {
        
    output.classification.idx = 0;
    output.classification.score = 0.24166666666666667;
    return;

    }

    }
    else {
        
    output.classification.idx = 3;
    output.classification.score = 0.21666666666666667;
    return;

    }

    }
    else {
        
    output.classification.idx = 0;
    output.classification.score = 0.24166666666666667;
    return;

    }

    }

    }
    else {
        
    output.classification.idx = 1;
    output.classification.score = 0.225;
    return;

    }

    }

            
        }

        bool isReady() {
            return true;
        }
};/**
 * DecisionTreeClassifier(max_depth=10, max_features='sqrt', min_samples_leaf=5,
                       random_state=1292965906)
 */
class _QDx2BT__decisiontree_8538128342879 {
    public:

        void operator()(Input& input, Output& output) {
            
                
    if (input._S0Owru__r < -0.21621620655059814f) {
        
    if (input._kutfua__b < -0.8275862038135529f) {
        
    output.classification.idx = 2;
    output.classification.score = 0.20833333333333334;
    return;

    }
    else {
        
    if (input._kutfua__b < -0.48275861144065857f) {
        
    output.classification.idx = 1;
    output.classification.score = 0.21666666666666667;
    return;

    }
    else {
        
    output.classification.idx = 1;
    output.classification.score = 0.21666666666666667;
    return;

    }

    }

    }
    else {
        
    if (input._svXR0N__g < -0.3396226465702057f) {
        
    output.classification.idx = 2;
    output.classification.score = 0.20833333333333334;
    return;

    }
    else {
        
    if (input._S0Owru__r < 0.0f) {
        
    output.classification.idx = 0;
    output.classification.score = 0.3;
    return;

    }
    else {
        
    if (input._S0Owru__r < 1.1891891956329346f) {
        
    if (input._kutfua__b < 0.6206896603107452f) {
        
    if (input._S0Owru__r < 0.21621620655059814f) {
        
    output.classification.idx = 0;
    output.classification.score = 0.3;
    return;

    }
    else {
        
    if (input._kutfua__b < 0.13793103769421577f) {
        
    output.classification.idx = 3;
    output.classification.score = 0.275;
    return;

    }
    else {
        
    if (input._S0Owru__r < 0.5405405461788177f) {
        
    output.classification.idx = 3;
    output.classification.score = 0.275;
    return;

    }
    else {
        
    output.classification.idx = 3;
    output.classification.score = 0.275;
    return;

    }

    }

    }

    }
    else {
        
    output.classification.idx = 0;
    output.classification.score = 0.3;
    return;

    }

    }
    else {
        
    output.classification.idx = 1;
    output.classification.score = 0.21666666666666667;
    return;

    }

    }

    }

    }

            
        }

        bool isReady() {
            return true;
        }
};/**
 * DecisionTreeClassifier(max_depth=10, max_features='sqrt', min_samples_leaf=5,
                       random_state=1502986208)
 */
class _O4W4eM__decisiontree_8538129552382 {
    public:

        void operator()(Input& input, Output& output) {
            
                
    if (input._kutfua__b < -0.41379310190677643f) {
        
    if (input._S0Owru__r < -1.0270270109176636f) {
        
    output.classification.idx = 1;
    output.classification.score = 0.15;
    return;

    }
    else {
        
    output.classification.idx = 2;
    output.classification.score = 0.25833333333333336;
    return;

    }

    }
    else {
        
    if (input._S0Owru__r < 0.21621620655059814f) {
        
    if (input._kutfua__b < 0.3448275737464428f) {
        
    if (input._kutfua__b < -0.27586207538843155f) {
        
    output.classification.idx = 0;
    output.classification.score = 0.31666666666666665;
    return;

    }
    else {
        
    output.classification.idx = 0;
    output.classification.score = 0.31666666666666665;
    return;

    }

    }
    else {
        
    output.classification.idx = 1;
    output.classification.score = 0.15;
    return;

    }

    }
    else {
        
    if (input._S0Owru__r < 0.864864856004715f) {
        
    if (input._kutfua__b < 0.13793103769421577f) {
        
    output.classification.idx = 3;
    output.classification.score = 0.275;
    return;

    }
    else {
        
    if (input._svXR0N__g < 0.30188679695129395f) {
        
    output.classification.idx = 0;
    output.classification.score = 0.31666666666666665;
    return;

    }
    else {
        
    output.classification.idx = 3;
    output.classification.score = 0.275;
    return;

    }

    }

    }
    else {
        
    output.classification.idx = 3;
    output.classification.score = 0.275;
    return;

    }

    }

    }

            
        }

        bool isReady() {
            return true;
        }
};/**
 * DecisionTreeClassifier(max_depth=10, max_features='sqrt', min_samples_leaf=5,
                       random_state=1968765050)
 */
class _9nmgcf__decisiontree_8538128869122 {
    public:

        void operator()(Input& input, Output& output) {
            
                
    if (input._kutfua__b < -0.41379310190677643f) {
        
    if (input._kutfua__b < -1.1034482717514038f) {
        
    output.classification.idx = 2;
    output.classification.score = 0.25;
    return;

    }
    else {
        
    if (input._S0Owru__r < -0.3243243247270584f) {
        
    output.classification.idx = 1;
    output.classification.score = 0.25833333333333336;
    return;

    }
    else {
        
    output.classification.idx = 2;
    output.classification.score = 0.25;
    return;

    }

    }

    }
    else {
        
    if (input._kutfua__b < 0.5517241209745407f) {
        
    if (input._kutfua__b < 0.0f) {
        
    if (input._kutfua__b < -0.27586207538843155f) {
        
    if (input._S0Owru__r < -0.10810810513794422f) {
        
    output.classification.idx = 1;
    output.classification.score = 0.25833333333333336;
    return;

    }
    else {
        
    output.classification.idx = 0;
    output.classification.score = 0.275;
    return;

    }

    }
    else {
        
    output.classification.idx = 0;
    output.classification.score = 0.275;
    return;

    }

    }
    else {
        
    if (input._svXR0N__g < 0.18867924809455872f) {
        
    if (input._kutfua__b < 0.13793103769421577f) {
        
    output.classification.idx = 3;
    output.classification.score = 0.21666666666666667;
    return;

    }
    else {
        
    output.classification.idx = 0;
    output.classification.score = 0.275;
    return;

    }

    }
    else {
        
    output.classification.idx = 3;
    output.classification.score = 0.21666666666666667;
    return;

    }

    }

    }
    else {
        
    if (input._kutfua__b < 1.58620685338974f) {
        
    if (input._S0Owru__r < 0.21621620655059814f) {
        
    output.classification.idx = 1;
    output.classification.score = 0.25833333333333336;
    return;

    }
    else {
        
    output.classification.idx = 0;
    output.classification.score = 0.275;
    return;

    }

    }
    else {
        
    output.classification.idx = 1;
    output.classification.score = 0.25833333333333336;
    return;

    }

    }

    }

            
        }

        bool isReady() {
            return true;
        }
};/**
 * DecisionTreeClassifier(max_depth=10, max_features='sqrt', min_samples_leaf=5,
                       random_state=1731570463)
 */
class _w5qDCS__decisiontree_8538128869266 {
    public:

        void operator()(Input& input, Output& output) {
            
                
    if (input._svXR0N__g < -0.4150943458080292f) {
        
    if (input._S0Owru__r < -0.4324324429035187f) {
        
    output.classification.idx = 2;
    output.classification.score = 0.225;
    return;

    }
    else {
        
    output.classification.idx = 2;
    output.classification.score = 0.225;
    return;

    }

    }
    else {
        
    if (input._kutfua__b < 1.3793103098869324f) {
        
    if (input._S0Owru__r < -0.2702702730894089f) {
        
    output.classification.idx = 1;
    output.classification.score = 0.225;
    return;

    }
    else {
        
    if (input._svXR0N__g < 0.18867924809455872f) {
        
    if (input._kutfua__b < -0.27586207538843155f) {
        
    output.classification.idx = 0;
    output.classification.score = 0.275;
    return;

    }
    else {
        
    if (input._kutfua__b < 0.0f) {
        
    output.classification.idx = 0;
    output.classification.score = 0.275;
    return;

    }
    else {
        
    output.classification.idx = 0;
    output.classification.score = 0.275;
    return;

    }

    }

    }
    else {
        
    if (input._kutfua__b < 0.8275862038135529f) {
        
    output.classification.idx = 3;
    output.classification.score = 0.275;
    return;

    }
    else {
        
    output.classification.idx = 0;
    output.classification.score = 0.275;
    return;

    }

    }

    }

    }
    else {
        
    if (input._kutfua__b < 2.896551728248596f) {
        
    output.classification.idx = 1;
    output.classification.score = 0.225;
    return;

    }
    else {
        
    output.classification.idx = 1;
    output.classification.score = 0.225;
    return;

    }

    }

    }

            
        }

        bool isReady() {
            return true;
        }
};/**
 * DecisionTreeClassifier(max_depth=10, max_features='sqrt', min_samples_leaf=5,
                       random_state=1439618311)
 */
class _l0jWEC__decisiontree_8538128869344 {
    public:

        void operator()(Input& input, Output& output) {
            
                
    if (input._svXR0N__g < -0.3396226465702057f) {
        
    if (input._svXR0N__g < -0.6415094435214996f) {
        
    if (input._svXR0N__g < -0.7924528419971466f) {
        
    output.classification.idx = 2;
    output.classification.score = 0.26666666666666666;
    return;

    }
    else {
        
    output.classification.idx = 2;
    output.classification.score = 0.26666666666666666;
    return;

    }

    }
    else {
        
    output.classification.idx = 2;
    output.classification.score = 0.26666666666666666;
    return;

    }

    }
    else {
        
    if (input._kutfua__b < 0.8275862038135529f) {
        
    if (input._S0Owru__r < 0.21621620655059814f) {
        
    if (input._kutfua__b < -0.13793103769421577f) {
        
    output.classification.idx = 0;
    output.classification.score = 0.25833333333333336;
    return;

    }
    else {
        
    output.classification.idx = 0;
    output.classification.score = 0.25833333333333336;
    return;

    }

    }
    else {
        
    if (input._kutfua__b < 0.13793103769421577f) {
        
    output.classification.idx = 3;
    output.classification.score = 0.3;
    return;

    }
    else {
        
    if (input._kutfua__b < 0.27586207538843155f) {
        
    output.classification.idx = 3;
    output.classification.score = 0.3;
    return;

    }
    else {
        
    output.classification.idx = 3;
    output.classification.score = 0.3;
    return;

    }

    }

    }

    }
    else {
        
    if (input._svXR0N__g < 0.9056603908538818f) {
        
    if (input._kutfua__b < 1.1724137663841248f) {
        
    output.classification.idx = 0;
    output.classification.score = 0.25833333333333336;
    return;

    }
    else {
        
    output.classification.idx = 0;
    output.classification.score = 0.25833333333333336;
    return;

    }

    }
    else {
        
    output.classification.idx = 1;
    output.classification.score = 0.175;
    return;

    }

    }

    }

            
        }

        bool isReady() {
            return true;
        }
};/**
 * DecisionTreeClassifier(max_depth=10, max_features='sqrt', min_samples_leaf=5,
                       random_state=1854609975)
 */
class _EY8ZgI__decisiontree_8538128458750 {
    public:

        void operator()(Input& input, Output& output) {
            
                
    if (input._svXR0N__g < -0.30188679695129395f) {
        
    if (input._kutfua__b < -0.6896551549434662f) {
        
    if (input._S0Owru__r < -0.5405405461788177f) {
        
    output.classification.idx = 1;
    output.classification.score = 0.24166666666666667;
    return;

    }
    else {
        
    output.classification.idx = 2;
    output.classification.score = 0.24166666666666667;
    return;

    }

    }
    else {
        
    if (input._S0Owru__r < -0.6486486345529556f) {
        
    output.classification.idx = 1;
    output.classification.score = 0.24166666666666667;
    return;

    }
    else {
        
    output.classification.idx = 2;
    output.classification.score = 0.24166666666666667;
    return;

    }

    }

    }
    else {
        
    if (input._svXR0N__g < 0.9056603908538818f) {
        
    if (input._S0Owru__r < 0.0f) {
        
    output.classification.idx = 0;
    output.classification.score = 0.23333333333333334;
    return;

    }
    else {
        
    if (input._kutfua__b < 0.6896551698446274f) {
        
    if (input._kutfua__b < -0.13793103769421577f) {
        
    output.classification.idx = 3;
    output.classification.score = 0.2833333333333333;
    return;

    }
    else {
        
    if (input._S0Owru__r < 0.5405405461788177f) {
        
    output.classification.idx = 3;
    output.classification.score = 0.2833333333333333;
    return;

    }
    else {
        
    output.classification.idx = 3;
    output.classification.score = 0.2833333333333333;
    return;

    }

    }

    }
    else {
        
    output.classification.idx = 0;
    output.classification.score = 0.23333333333333334;
    return;

    }

    }

    }
    else {
        
    output.classification.idx = 1;
    output.classification.score = 0.24166666666666667;
    return;

    }

    }

            
        }

        bool isReady() {
            return true;
        }
};/**
 * DecisionTreeClassifier(max_depth=10, max_features='sqrt', min_samples_leaf=5,
                       random_state=721313735)
 */
class _8cUgat__decisiontree_8538128883464 {
    public:

        void operator()(Input& input, Output& output) {
            
                
    if (input._svXR0N__g < -0.4150943458080292f) {
        
    if (input._svXR0N__g < -0.5660377442836761f) {
        
    if (input._svXR0N__g < -0.6415094435214996f) {
        
    if (input._S0Owru__r < -0.9729729890823364f) {
        
    output.classification.idx = 1;
    output.classification.score = 0.24166666666666667;
    return;

    }
    else {
        
    output.classification.idx = 2;
    output.classification.score = 0.25;
    return;

    }

    }
    else {
        
    output.classification.idx = 1;
    output.classification.score = 0.24166666666666667;
    return;

    }

    }
    else {
        
    output.classification.idx = 2;
    output.classification.score = 0.25;
    return;

    }

    }
    else {
        
    if (input._kutfua__b < 1.8620688915252686f) {
        
    if (input._S0Owru__r < 0.21621620655059814f) {
        
    if (input._kutfua__b < 0.0f) {
        
    if (input._svXR0N__g < -0.11320754885673523f) {
        
    output.classification.idx = 0;
    output.classification.score = 0.26666666666666666;
    return;

    }
    else {
        
    output.classification.idx = 0;
    output.classification.score = 0.26666666666666666;
    return;

    }

    }
    else {
        
    output.classification.idx = 0;
    output.classification.score = 0.26666666666666666;
    return;

    }

    }
    else {
        
    if (input._svXR0N__g < 0.49056604504585266f) {
        
    if (input._svXR0N__g < 0.2641509473323822f) {
        
    output.classification.idx = 3;
    output.classification.score = 0.24166666666666667;
    return;

    }
    else {
        
    output.classification.idx = 3;
    output.classification.score = 0.24166666666666667;
    return;

    }

    }
    else {
        
    output.classification.idx = 0;
    output.classification.score = 0.26666666666666666;
    return;

    }

    }

    }
    else {
        
    output.classification.idx = 1;
    output.classification.score = 0.24166666666666667;
    return;

    }

    }

            
        }

        bool isReady() {
            return true;
        }
};/**
 * DecisionTreeClassifier(max_depth=10, max_features='sqrt', min_samples_leaf=5,
                       random_state=46282947)
 */
class _nd4XYO__decisiontree_8538128883242 {
    public:

        void operator()(Input& input, Output& output) {
            
                
    if (input._kutfua__b < -0.41379310190677643f) {
        
    if (input._S0Owru__r < -0.9729729890823364f) {
        
    output.classification.idx = 1;
    output.classification.score = 0.23333333333333334;
    return;

    }
    else {
        
    output.classification.idx = 2;
    output.classification.score = 0.30833333333333335;
    return;

    }

    }
    else {
        
    if (input._S0Owru__r < -0.2702702730894089f) {
        
    output.classification.idx = 1;
    output.classification.score = 0.23333333333333334;
    return;

    }
    else {
        
    if (input._svXR0N__g < 0.9056603908538818f) {
        
    if (input._kutfua__b < 0.0f) {
        
    if (input._kutfua__b < -0.27586207538843155f) {
        
    output.classification.idx = 3;
    output.classification.score = 0.24166666666666667;
    return;

    }
    else {
        
    output.classification.idx = 0;
    output.classification.score = 0.21666666666666667;
    return;

    }

    }
    else {
        
    if (input._svXR0N__g < 0.18867924809455872f) {
        
    output.classification.idx = 0;
    output.classification.score = 0.21666666666666667;
    return;

    }
    else {
        
    if (input._svXR0N__g < 0.49056604504585266f) {
        
    output.classification.idx = 3;
    output.classification.score = 0.24166666666666667;
    return;

    }
    else {
        
    output.classification.idx = 0;
    output.classification.score = 0.21666666666666667;
    return;

    }

    }

    }

    }
    else {
        
    output.classification.idx = 1;
    output.classification.score = 0.23333333333333334;
    return;

    }

    }

    }

            
        }

        bool isReady() {
            return true;
        }
};/**
 * DecisionTreeClassifier(max_depth=10, max_features='sqrt', min_samples_leaf=5,
                       random_state=647353104)
 */
class _wzzxEA__decisiontree_8538128882702 {
    public:

        void operator()(Input& input, Output& output) {
            
                
    if (input._S0Owru__r < -0.21621620655059814f) {
        
    if (input._S0Owru__r < -0.9729729890823364f) {
        
    output.classification.idx = 1;
    output.classification.score = 0.25;
    return;

    }
    else {
        
    if (input._svXR0N__g < -0.5283018946647644f) {
        
    output.classification.idx = 2;
    output.classification.score = 0.2;
    return;

    }
    else {
        
    output.classification.idx = 1;
    output.classification.score = 0.25;
    return;

    }

    }

    }
    else {
        
    if (input._svXR0N__g < -0.37735849618911743f) {
        
    output.classification.idx = 2;
    output.classification.score = 0.2;
    return;

    }
    else {
        
    if (input._kutfua__b < 1.7241379022598267f) {
        
    if (input._kutfua__b < 0.6896551698446274f) {
        
    if (input._S0Owru__r < 0.21621620655059814f) {
        
    if (input._kutfua__b < -0.13793103769421577f) {
        
    output.classification.idx = 0;
    output.classification.score = 0.325;
    return;

    }
    else {
        
    output.classification.idx = 0;
    output.classification.score = 0.325;
    return;

    }

    }
    else {
        
    if (input._svXR0N__g < 0.18867924809455872f) {
        
    output.classification.idx = 0;
    output.classification.score = 0.325;
    return;

    }
    else {
        
    output.classification.idx = 3;
    output.classification.score = 0.225;
    return;

    }

    }

    }
    else {
        
    output.classification.idx = 0;
    output.classification.score = 0.325;
    return;

    }

    }
    else {
        
    output.classification.idx = 1;
    output.classification.score = 0.25;
    return;

    }

    }

    }

            
        }

        bool isReady() {
            return true;
        }
};/**
 * DecisionTreeClassifier(max_depth=10, max_features='sqrt', min_samples_leaf=5,
                       random_state=198276652)
 */
class _CqVmvi__decisiontree_8538129272401 {
    public:

        void operator()(Input& input, Output& output) {
            
                
    if (input._svXR0N__g < -0.4150943458080292f) {
        
    if (input._svXR0N__g < -0.6415094435214996f) {
        
    if (input._svXR0N__g < -0.7924528419971466f) {
        
    output.classification.idx = 2;
    output.classification.score = 0.30833333333333335;
    return;

    }
    else {
        
    output.classification.idx = 2;
    output.classification.score = 0.30833333333333335;
    return;

    }

    }
    else {
        
    if (input._S0Owru__r < -0.10810810513794422f) {
        
    output.classification.idx = 2;
    output.classification.score = 0.30833333333333335;
    return;

    }
    else {
        
    output.classification.idx = 2;
    output.classification.score = 0.30833333333333335;
    return;

    }

    }

    }
    else {
        
    if (input._S0Owru__r < -0.2702702730894089f) {
        
    output.classification.idx = 1;
    output.classification.score = 0.23333333333333334;
    return;

    }
    else {
        
    if (input._kutfua__b < 2.0f) {
        
    if (input._kutfua__b < 0.27586207538843155f) {
        
    if (input._svXR0N__g < 0.15094339847564697f) {
        
    if (input._kutfua__b < 0.0f) {
        
    output.classification.idx = 0;
    output.classification.score = 0.24166666666666667;
    return;

    }
    else {
        
    output.classification.idx = 0;
    output.classification.score = 0.24166666666666667;
    return;

    }

    }
    else {
        
    output.classification.idx = 3;
    output.classification.score = 0.21666666666666667;
    return;

    }

    }
    else {
        
    if (input._S0Owru__r < 1.081081062555313f) {
        
    output.classification.idx = 0;
    output.classification.score = 0.24166666666666667;
    return;

    }
    else {
        
    output.classification.idx = 0;
    output.classification.score = 0.24166666666666667;
    return;

    }

    }

    }
    else {
        
    output.classification.idx = 1;
    output.classification.score = 0.23333333333333334;
    return;

    }

    }

    }

            
        }

        bool isReady() {
            return true;
        }
};/**
 * DecisionTreeClassifier(max_depth=10, max_features='sqrt', min_samples_leaf=5,
                       random_state=485226452)
 */
class _HNg2rG__decisiontree_8538129272404 {
    public:

        void operator()(Input& input, Output& output) {
            
                
    if (input._svXR0N__g < -0.4150943458080292f) {
        
    if (input._S0Owru__r < -0.9189189076423645f) {
        
    output.classification.idx = 1;
    output.classification.score = 0.275;
    return;

    }
    else {
        
    output.classification.idx = 2;
    output.classification.score = 0.26666666666666666;
    return;

    }

    }
    else {
        
    if (input._kutfua__b < 1.3793103098869324f) {
        
    if (input._S0Owru__r < -0.3243243247270584f) {
        
    output.classification.idx = 1;
    output.classification.score = 0.275;
    return;

    }
    else {
        
    if (input._kutfua__b < 0.41379310190677643f) {
        
    if (input._S0Owru__r < 0.4864864945411682f) {
        
    if (input._S0Owru__r < 0.10810810513794422f) {
        
    output.classification.idx = 0;
    output.classification.score = 0.25;
    return;

    }
    else {
        
    output.classification.idx = 0;
    output.classification.score = 0.25;
    return;

    }

    }
    else {
        
    output.classification.idx = 3;
    output.classification.score = 0.20833333333333334;
    return;

    }

    }
    else {
        
    output.classification.idx = 0;
    output.classification.score = 0.25;
    return;

    }

    }

    }
    else {
        
    if (input._svXR0N__g < 1.8867924809455872f) {
        
    output.classification.idx = 1;
    output.classification.score = 0.275;
    return;

    }
    else {
        
    output.classification.idx = 1;
    output.classification.score = 0.275;
    return;

    }

    }

    }

            
        }

        bool isReady() {
            return true;
        }
};/**
 * DecisionTreeClassifier(max_depth=10, max_features='sqrt', min_samples_leaf=5,
                       random_state=1382852470)
 */
class _NdxEs5__decisiontree_8538128467027 {
    public:

        void operator()(Input& input, Output& output) {
            
                
    if (input._kutfua__b < -0.41379310190677643f) {
        
    if (input._svXR0N__g < -0.5660377442836761f) {
        
    if (input._kutfua__b < -0.9655172228813171f) {
        
    output.classification.idx = 2;
    output.classification.score = 0.18333333333333332;
    return;

    }
    else {
        
    output.classification.idx = 2;
    output.classification.score = 0.18333333333333332;
    return;

    }

    }
    else {
        
    output.classification.idx = 2;
    output.classification.score = 0.18333333333333332;
    return;

    }

    }
    else {
        
    if (input._S0Owru__r < -0.2702702730894089f) {
        
    output.classification.idx = 1;
    output.classification.score = 0.25833333333333336;
    return;

    }
    else {
        
    if (input._S0Owru__r < 0.4324324429035187f) {
        
    if (input._S0Owru__r < 0.0f) {
        
    output.classification.idx = 0;
    output.classification.score = 0.275;
    return;

    }
    else {
        
    if (input._svXR0N__g < 0.11320754885673523f) {
        
    output.classification.idx = 0;
    output.classification.score = 0.275;
    return;

    }
    else {
        
    output.classification.idx = 3;
    output.classification.score = 0.2833333333333333;
    return;

    }

    }

    }
    else {
        
    if (input._kutfua__b < 0.7586206793785095f) {
        
    output.classification.idx = 3;
    output.classification.score = 0.2833333333333333;
    return;

    }
    else {
        
    output.classification.idx = 0;
    output.classification.score = 0.275;
    return;

    }

    }

    }

    }

            
        }

        bool isReady() {
            return true;
        }
};/**
 * DecisionTreeClassifier(max_depth=10, max_features='sqrt', min_samples_leaf=5,
                       random_state=1749571533)
 */
class _5teN7L__decisiontree_8538129530674 {
    public:

        void operator()(Input& input, Output& output) {
            
                
    if (input._kutfua__b < -0.41379310190677643f) {
        
    if (input._kutfua__b < -0.6896551549434662f) {
        
    if (input._S0Owru__r < -0.8648648858070374f) {
        
    output.classification.idx = 1;
    output.classification.score = 0.26666666666666666;
    return;

    }
    else {
        
    output.classification.idx = 2;
    output.classification.score = 0.31666666666666665;
    return;

    }

    }
    else {
        
    output.classification.idx = 1;
    output.classification.score = 0.26666666666666666;
    return;

    }

    }
    else {
        
    if (input._svXR0N__g < 0.9056603908538818f) {
        
    if (input._svXR0N__g < 0.18867924809455872f) {
        
    if (input._svXR0N__g < -0.11320754885673523f) {
        
    output.classification.idx = 0;
    output.classification.score = 0.20833333333333334;
    return;

    }
    else {
        
    if (input._S0Owru__r < 0.21621620655059814f) {
        
    output.classification.idx = 0;
    output.classification.score = 0.20833333333333334;
    return;

    }
    else {
        
    output.classification.idx = 0;
    output.classification.score = 0.20833333333333334;
    return;

    }

    }

    }
    else {
        
    if (input._S0Owru__r < 0.7567567527294159f) {
        
    output.classification.idx = 3;
    output.classification.score = 0.20833333333333334;
    return;

    }
    else {
        
    if (input._svXR0N__g < 0.49056604504585266f) {
        
    output.classification.idx = 3;
    output.classification.score = 0.20833333333333334;
    return;

    }
    else {
        
    output.classification.idx = 0;
    output.classification.score = 0.20833333333333334;
    return;

    }

    }

    }

    }
    else {
        
    output.classification.idx = 1;
    output.classification.score = 0.26666666666666666;
    return;

    }

    }

            
        }

        bool isReady() {
            return true;
        }
};/**
 * DecisionTreeClassifier(max_depth=10, max_features='sqrt', min_samples_leaf=5,
                       random_state=1523923710)
 */
class _9ZdEen__decisiontree_8538129530731 {
    public:

        void operator()(Input& input, Output& output) {
            
                
    if (input._svXR0N__g < -0.4150943458080292f) {
        
    if (input._kutfua__b < -0.6896551549434662f) {
        
    if (input._S0Owru__r < -0.4324324429035187f) {
        
    output.classification.idx = 2;
    output.classification.score = 0.35833333333333334;
    return;

    }
    else {
        
    output.classification.idx = 2;
    output.classification.score = 0.35833333333333334;
    return;

    }

    }
    else {
        
    output.classification.idx = 2;
    output.classification.score = 0.35833333333333334;
    return;

    }

    }
    else {
        
    if (input._kutfua__b < 0.8275862038135529f) {
        
    if (input._kutfua__b < -0.13793103769421577f) {
        
    if (input._S0Owru__r < 0.0f) {
        
    output.classification.idx = 0;
    output.classification.score = 0.25833333333333336;
    return;

    }
    else {
        
    output.classification.idx = 3;
    output.classification.score = 0.24166666666666667;
    return;

    }

    }
    else {
        
    if (input._svXR0N__g < 0.18867924809455872f) {
        
    output.classification.idx = 0;
    output.classification.score = 0.25833333333333336;
    return;

    }
    else {
        
    output.classification.idx = 3;
    output.classification.score = 0.24166666666666667;
    return;

    }

    }

    }
    else {
        
    if (input._S0Owru__r < 0.5405405312776566f) {
        
    output.classification.idx = 1;
    output.classification.score = 0.14166666666666666;
    return;

    }
    else {
        
    output.classification.idx = 0;
    output.classification.score = 0.25833333333333336;
    return;

    }

    }

    }

            
        }

        bool isReady() {
            return true;
        }
};/**
 * DecisionTreeClassifier(max_depth=10, max_features='sqrt', min_samples_leaf=5,
                       random_state=1301163833)
 */
class _XyWWqO__decisiontree_8538128430403 {
    public:

        void operator()(Input& input, Output& output) {
            
                
    if (input._S0Owru__r < 0.10810810513794422f) {
        
    if (input._S0Owru__r < -0.8648648858070374f) {
        
    output.classification.idx = 1;
    output.classification.score = 0.275;
    return;

    }
    else {
        
    if (input._svXR0N__g < -0.3396226465702057f) {
        
    output.classification.idx = 2;
    output.classification.score = 0.23333333333333334;
    return;

    }
    else {
        
    output.classification.idx = 1;
    output.classification.score = 0.275;
    return;

    }

    }

    }
    else {
        
    if (input._svXR0N__g < 0.9433962404727936f) {
        
    if (input._kutfua__b < 0.8275862038135529f) {
        
    if (input._S0Owru__r < 0.5405405461788177f) {
        
    if (input._kutfua__b < 0.13793103769421577f) {
        
    output.classification.idx = 3;
    output.classification.score = 0.225;
    return;

    }
    else {
        
    output.classification.idx = 0;
    output.classification.score = 0.26666666666666666;
    return;

    }

    }
    else {
        
    output.classification.idx = 3;
    output.classification.score = 0.225;
    return;

    }

    }
    else {
        
    output.classification.idx = 0;
    output.classification.score = 0.26666666666666666;
    return;

    }

    }
    else {
        
    output.classification.idx = 1;
    output.classification.score = 0.275;
    return;

    }

    }

            
        }

        bool isReady() {
            return true;
        }
};/**
 * DecisionTreeClassifier(max_depth=10, max_features='sqrt', min_samples_leaf=5,
                       random_state=378174086)
 */
class _AN1Qre__decisiontree_8538128430562 {
    public:

        void operator()(Input& input, Output& output) {
            
                
    if (input._kutfua__b < -0.41379310190677643f) {
        
    if (input._kutfua__b < -0.6896551549434662f) {
        
    if (input._svXR0N__g < -0.7924528419971466f) {
        
    output.classification.idx = 2;
    output.classification.score = 0.2;
    return;

    }
    else {
        
    output.classification.idx = 2;
    output.classification.score = 0.2;
    return;

    }

    }
    else {
        
    output.classification.idx = 1;
    output.classification.score = 0.3;
    return;

    }

    }
    else {
        
    if (input._kutfua__b < 1.517241358757019f) {
        
    if (input._svXR0N__g < 0.18867924809455872f) {
        
    if (input._svXR0N__g < -0.11320754885673523f) {
        
    output.classification.idx = 0;
    output.classification.score = 0.275;
    return;

    }
    else {
        
    if (input._svXR0N__g < 0.03773584961891174f) {
        
    output.classification.idx = 0;
    output.classification.score = 0.275;
    return;

    }
    else {
        
    output.classification.idx = 0;
    output.classification.score = 0.275;
    return;

    }

    }

    }
    else {
        
    if (input._kutfua__b < 0.8275862038135529f) {
        
    output.classification.idx = 3;
    output.classification.score = 0.225;
    return;

    }
    else {
        
    output.classification.idx = 0;
    output.classification.score = 0.275;
    return;

    }

    }

    }
    else {
        
    output.classification.idx = 1;
    output.classification.score = 0.3;
    return;

    }

    }

            
        }

        bool isReady() {
            return true;
        }
};

class _1BtZaq__randomforest_8538128444427 {
    public:
        void operator()(Input& input, Output& output) {
            Output treeOutput;
            float scores[4] = { 0 };

            // iterate over trees
            
                tree1(input, treeOutput);
                scores[treeOutput.classification.idx] += 1;
            
                tree2(input, treeOutput);
                scores[treeOutput.classification.idx] += 1;
            
                tree3(input, treeOutput);
                scores[treeOutput.classification.idx] += 1;
            
                tree4(input, treeOutput);
                scores[treeOutput.classification.idx] += 1;
            
                tree5(input, treeOutput);
                scores[treeOutput.classification.idx] += 1;
            
                tree6(input, treeOutput);
                scores[treeOutput.classification.idx] += 1;
            
                tree7(input, treeOutput);
                scores[treeOutput.classification.idx] += 1;
            
                tree8(input, treeOutput);
                scores[treeOutput.classification.idx] += 1;
            
                tree9(input, treeOutput);
                scores[treeOutput.classification.idx] += 1;
            
                tree10(input, treeOutput);
                scores[treeOutput.classification.idx] += 1;
            
                tree11(input, treeOutput);
                scores[treeOutput.classification.idx] += 1;
            
                tree12(input, treeOutput);
                scores[treeOutput.classification.idx] += 1;
            
                tree13(input, treeOutput);
                scores[treeOutput.classification.idx] += 1;
            
                tree14(input, treeOutput);
                scores[treeOutput.classification.idx] += 1;
            
                tree15(input, treeOutput);
                scores[treeOutput.classification.idx] += 1;
            
                tree16(input, treeOutput);
                scores[treeOutput.classification.idx] += 1;
            
                tree17(input, treeOutput);
                scores[treeOutput.classification.idx] += 1;
            
                tree18(input, treeOutput);
                scores[treeOutput.classification.idx] += 1;
            
                tree19(input, treeOutput);
                scores[treeOutput.classification.idx] += 1;
            
                tree20(input, treeOutput);
                scores[treeOutput.classification.idx] += 1;
            

            // get output with highest vote
            output.classification.idx = 0;
            output.classification.score = scores[0];

            for (uint8_t i = 1; i < 4; i++) {
                if (scores[i] > output.classification.score) {
                    output.classification.idx = i;
                    output.classification.score = scores[i];
                }
            }
        }

        /**
         * Always ready
         */
        bool isReady() {
            return true;
        }

    protected:
        
            _xCKXbE__decisiontree_8538128331201 tree1;
        
            _rOGxgn__decisiontree_8538128852318 tree2;
        
            _jvaidt__decisiontree_8538128852369 tree3;
        
            _xWGkvJ__decisiontree_8538128852774 tree4;
        
            _QDx2BT__decisiontree_8538128342879 tree5;
        
            _O4W4eM__decisiontree_8538129552382 tree6;
        
            _9nmgcf__decisiontree_8538128869122 tree7;
        
            _w5qDCS__decisiontree_8538128869266 tree8;
        
            _l0jWEC__decisiontree_8538128869344 tree9;
        
            _EY8ZgI__decisiontree_8538128458750 tree10;
        
            _8cUgat__decisiontree_8538128883464 tree11;
        
            _nd4XYO__decisiontree_8538128883242 tree12;
        
            _wzzxEA__decisiontree_8538128882702 tree13;
        
            _CqVmvi__decisiontree_8538129272401 tree14;
        
            _HNg2rG__decisiontree_8538129272404 tree15;
        
            _NdxEs5__decisiontree_8538128467027 tree16;
        
            _5teN7L__decisiontree_8538129530674 tree17;
        
            _9ZdEen__decisiontree_8538129530731 tree18;
        
            _XyWWqO__decisiontree_8538128430403 tree19;
        
            _AN1Qre__decisiontree_8538128430562 tree20;
        
};
    

    /**
     * Chain class
     * Chain(blocks=[Scale(method=robust, offsets=[20.5 20.  16.5], scales=[ 9.25 13.25  7.25]), RandomForestClassifier(max_depth=10, min_samples_leaf=5, n_estimators=20)])
     */
     class FruitChain {
        public:
            Input input;
            Output output;

            /**
             * Transform array input
             */
            bool operator()(float *inputs) {
                return operator()(inputs[0], inputs[1], inputs[2]);
            }

            /**
             * Transform const array input
             */
            bool operator()(const float *inputs) {
                return operator()(inputs[0], inputs[1], inputs[2]);
            }

            /**
             * Transform variadic input
             */
            bool operator()(const float _S0Owru__r, const float _svXR0N__g, const float _kutfua__b) {
                // assign variables to input
                
                    input._S0Owru__r = _S0Owru__r;
                
                    input._svXR0N__g = _svXR0N__g;
                
                    input._kutfua__b = _kutfua__b;
                

                // run blocks
                
                    // Scale(method=robust, offsets=[20.5 20.  16.5], scales=[ 9.25 13.25  7.25])
                    block1(input, output);

                    if (!block1.isReady())
                        return false;
                
                    // RandomForestClassifier(max_depth=10, min_samples_leaf=5, n_estimators=20)
                    block2(input, output);

                    if (!block2.isReady())
                        return false;
                

                
    switch (output.classification.idx) {
        
        case 0:
            strcpy(output.classification.label, "coconut");
            break;
        
        case 1:
            strcpy(output.classification.label, "none");
            break;
        
        case 2:
            strcpy(output.classification.label, "tomato");
            break;
        
        case 3:
            strcpy(output.classification.label, "yellow_apple");
            break;
        
        default:
            strcpy(output.classification.label, "unknown");
    }


                return true;
            }

        protected:
            
                // Scale(method=robust, offsets=[20.5 20.  16.5], scales=[ 9.25 13.25  7.25])
                _aCm4WH__scale_8538129521428 block1;
            
                // RandomForestClassifier(max_depth=10, min_samples_leaf=5, n_estimators=20)
                _1BtZaq__randomforest_8538128444427 block2;
            
    };
}