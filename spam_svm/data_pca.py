from sklearn.model_selection import train_test_split
from scipy import sparse, io
from sklearn.decomposition import PCA


def dimensionality_reduction(training_data, test_data):
    n_components = 1000
    pca = PCA(n_components=n_components, whiten=True)
    pca.fit(training_data)
    training_data_transform = sparse.csr_matrix(pca.transform(training_data))
    test_data_transform = sparse.csr_matrix(pca.transform(test_data))
    #random_projections
    #feature_agglomeration
    return training_data_transform, test_data_transform

def split_data(content, label):
    training_data, test_data, training_target, test_target = train_test_split(
        content, label, test_size=0.2, random_state=20)
    return training_data, test_data, training_target, test_target