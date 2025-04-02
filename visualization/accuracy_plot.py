import plotly.graph_objects as go
import plotly.io as pio
import pandas as pd
import numpy as np

# approximation csv
df = pd.read_csv("../data/accuracy.csv")

df["approx"] = pd.to_numeric(df["approx"], errors="coerce")
df["value"] = pd.to_numeric(df["value"], errors="coerce")
df["error"] = pd.to_numeric(df["error"], errors="coerce")
df["nodes"] = pd.to_numeric(df["nodes"], errors="coerce")

approx: float = df["approx"]
value: float = df["value"]
nodes: float = df["nodes"]
error: float = df["error"]

# true value csv
df_true = pd.read_csv("../data/nodes_values_true.csv")

df_true["y"] = pd.to_numeric(df_true["y"], errors="coerce")
df_true["x"] = pd.to_numeric(df_true["x"], errors="coerce")

value_true: float = df_true["y"]
nodes_true: float = df_true["x"]

fig = go.Figure()

fig.add_trace(
    go.Scatter(
        x=nodes,
        y=error,
        mode="lines+markers",
        name="Error %",
        line_shape='spline',
        line=dict(
            color="red",
            width=4
        ),
        marker=dict(
            size=10,
            line=dict(width=2)
        )
    )
)

fig.update_layout(
    title=dict(text="Lagrange Interpolation Inaccuracy", font=dict(size=50), automargin=True),
    xaxis=dict(title="Node Value"),
    yaxis=dict(title="Error %", type="log"),
    font=dict(size=30),
    template="plotly_dark",
    hovermode="x unified"
)

pio.write_image(fig, "plots/error_pct.png", scale=3, height=1080, width=1920)

fig2 = go.Figure()

fig2.add_trace(
    go.Scatter(
        x=nodes_true,
        y=value_true,
        mode="lines+markers",
        name="Values",
        line_shape='spline',
        line=dict(
            color="red",
            width=4
        ),
        marker=dict(
            size=10,
            line=dict(width=2)
        )
    )
)

fig2.add_trace(
    go.Scatter(
        x=nodes,
        y=approx,
        mode="lines+markers",
        name="Approximations",
        line_shape='spline',
        line=dict(
            color="purple",
            width=4
        ),
        marker=dict(
            size=10,
            line=dict(width=2)
        )
    )
)

fig2.update_layout(
    title=dict(text="Value vs. Approximation", font=dict(size=50), automargin=True),
    xaxis=dict(title="Node Value"),
    yaxis=dict(
        title="Values & Approximations",
        type="log"
    ),
    font=dict(size=30, color="green"),
    legend=dict(title=dict(text="Type")),
    template="plotly_dark",
    hovermode="x unified"
)

pio.write_image(fig2, "plots/ValVsApprox.png", scale=3, height=1080, width=1920)

# function plot

fig3 = go.Figure()

fig3.add_trace(
    go.Scatter(
        x=nodes_true,
        y=value_true,
        mode="lines+markers",
        name="Values",
        line_shape='spline',
        line=dict(
            color="red",
            width=4
        ),
        marker=dict(
            size=10,
            line=dict(width=2)
        )
    )
)

range_val = [0, 1.1]

fig3.update_layout(
    title=dict(text="Nodes and Values", font=dict(size=50), automargin=True),
    xaxis=dict(
        title="Node",
        range=[-1, 1]
    ),
    yaxis=dict(
        title="Values",
        range=range_val
    ),
    font=dict(size=30, color="white"),
    legend=dict(title=dict(text="Type")),
    template="plotly_dark",
    hovermode="x unified"
)

pio.write_image(fig3, "plots/NodeVal.png", scale=3, height=1080, width=1920)