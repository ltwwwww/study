import numpy as np
from sklearn import svm
from sklearn import metrics
import json
from sklearn.model_selection import cross_val_score
import joblib
from matplotlib.colors import Normalize
from sklearn.svm import SVC
from sklearn.model_selection import StratifiedShuffleSplit
from sklearn.model_selection import GridSearchCV
from sklearn.model_selection import ShuffleSplit
from scipy import sparse, io
from data_pca import split_data
from data_pca import dimensionality_reduction

class TrainerLinear:
    def __init__(self, training_data, training_target):
        self.training_data = training_data
        self.training_target = training_target
        self.clf = svm.SVC(C=1, class_weight=None, coef0=0.0,
                           decision_function_shape='ovo', degree=3, gamma='auto',
                           kernel='linear', max_iter=-1, probability=False,
                           random_state=None, shrinking=True, tol=0.001, verbose=False)

    def learn_best_param(self):
        C_range = np.logspace(-2, 10, 13)
        param_grid = dict(C=C_range)
        cv = StratifiedShuffleSplit(n_splits=5, test_size=0.2, random_state=42)
        grid = GridSearchCV(SVC(), param_grid=param_grid, cv=cv)
        grid.fit(self.training_data, self.training_target)
        self.clf.set_params(C=grid.best_params_['C'])
        print("The best parameters are %s with a score of %0.2f"
              % (grid.best_params_, grid.best_score_))

    def train_classifier(self):
        self.clf.fit(self.training_data, self.training_target)
        joblib.dump(self.clf, 'model/SVM_linear_estimator.pkl')
        training_result = self.clf.predict(self.training_data)
        print(metrics.classification_report(self.training_target, training_result))

    def cross_validation(self):
        cv = ShuffleSplit(n_splits=5, test_size=0.2, random_state=20)
        scores = cross_val_score(self.clf, self.training_data, self.training_target, cv=cv, scoring='f1_macro')
        print(scores)
        print("Accuracy: %0.2f (+/- %0.2f)" % (scores.mean(), scores.std() * 2))


if '__main__' == __name__:
    content = io.mmread('../Data/word_vector.mtx')
    # with open('../Data/word_vector.mtx', 'r') as f:
    #     content = json.load(f)
    with open('../Data/train_label.json', 'r') as f:
        label = json.load(f)
    # low_content = dimensionality_reduction(content.todense(),content.todense())

    training_data, test_data, training_target, test_target = split_data(content, label)
    training_data, test_data = dimensionality_reduction(training_data.todense(), test_data.todense())
    # training_data = training_data.data.reshape(training_data.shape)
    # test_data = test_data.data.reshape(test_data.shape)
    Trainer = TrainerLinear(training_data, training_target)
    # Trainer.learn_best_param()
    Trainer.train_classifier()
    print('ok')


