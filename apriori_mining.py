import pandas as pd
from sklearn.datasets import load_iris, fetch_openml
from sklearn.preprocessing import KBinsDiscretizer
from mlxtend.frequent_patterns import apriori, association_rules

def mine_rules(data, min_support=0.2, min_confidence=0.7):
    encoded = pd.get_dummies(data.astype(str)).astype(bool)
    frequent = apriori(encoded, min_support=min_support, use_colnames=True)

    if frequent.empty:
        print("No frequent itemsets found.")
        return

    rules = association_rules(
        frequent, metric="confidence", min_threshold=min_confidence
    )

    if rules.empty:
        print("No association rules found.")
        return

    rules["antecedents"] = rules["antecedents"].apply(
        lambda items: ", ".join(sorted(items))
    )
    rules["consequents"] = rules["consequents"].apply(
        lambda items: ", ".join(sorted(items))
    )
    print(rules[["antecedents", "consequents", "support", "confidence", "lift"]]
          .to_string(index=False))


# 1. Weather dataset (14 examples)
weather = pd.DataFrame({
    "outlook": ["sunny", "sunny", "overcast", "rainy", "rainy", "rainy",
                "overcast", "sunny", "sunny", "rainy", "sunny", "overcast",
                "overcast", "rainy"],
    "temperature": ["hot", "hot", "hot", "mild", "cool", "cool", "cool",
                    "mild", "cool", "mild", "mild", "mild", "hot", "mild"],
    "humidity": ["high", "high", "high", "high", "normal", "normal",
                 "normal", "high", "normal", "normal", "normal", "high",
                 "normal", "high"],
    "windy": ["FALSE", "TRUE", "FALSE", "FALSE", "FALSE", "TRUE",
              "TRUE", "FALSE", "FALSE", "FALSE", "TRUE", "TRUE",
              "FALSE", "TRUE"],
    "play": ["no", "no", "yes", "yes", "yes", "no", "yes", "no",
             "yes", "yes", "yes", "yes", "yes", "no"]
})

print("\n=== WEATHER DATASET ===")
mine_rules(weather, min_support=0.2, min_confidence=0.7)

# 2. Iris dataset: discretize numeric measurements into 3 bins
iris_data = load_iris(as_frame=True)
iris = iris_data.data.copy()
iris["class"] = iris_data.target.map(
    dict(enumerate(iris_data.target_names))
)

discretizer = KBinsDiscretizer(
    n_bins=3, encode="ordinal", strategy="quantile"
)
iris_bins = discretizer.fit_transform(iris.iloc[:, :4])

iris_discrete = pd.DataFrame(
    iris_bins.astype(int),
    columns=["sepal_length", "sepal_width", "petal_length", "petal_width"]
).astype(str)

for column in iris_discrete.columns:
    iris_discrete[column] = column + "_bin_" + iris_discrete[column]
iris_discrete["class"] = iris["class"].to_numpy()

print("\n=== IRIS AFTER DISCRETIZATION ===")
mine_rules(iris_discrete, min_support=0.1, min_confidence=0.7)

# 3. Glass dataset: fetch from OpenML (internet required)
print("\n=== GLASS DATASET ===")
try:
    glass = fetch_openml(name="glass", version=1, as_frame=True)
    glass_df = glass.data.copy()
    glass_df["class"] = glass.target.astype(str).to_numpy()
    glass_df = glass_df.apply(
        lambda col: pd.to_numeric(col, errors="ignore")
    ).dropna()

    # Resample to 50% of rows
    glass_sample = glass_df.sample(frac=0.5, random_state=42)
    print("Original rows:", len(glass_df))
    print("Resampled rows:", len(glass_sample))

    numeric_columns = glass_sample.select_dtypes(include="number").columns
    glass_discrete = glass_sample.copy()
    glass_discrete.loc[:, numeric_columns] = KBinsDiscretizer(
        n_bins=3, encode="ordinal", strategy="quantile"
    ).fit_transform(glass_sample[numeric_columns]).astype(int)

    for column in numeric_columns:
        glass_discrete[column] = (
            column + "_bin_" + glass_discrete[column].astype(str)
        )

    print("\n=== GLASS AFTER RESAMPLING AND DISCRETIZATION ===")
    mine_rules(glass_discrete, min_support=0.1, min_confidence=0.7)

except Exception as error:
    print("Glass dataset could not be downloaded.")
    print("Check internet connection and OpenML availability.")
    print("Details:", error)
