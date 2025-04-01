import plotly.graph_objects as go
import plotly.io as pio
import pandas as pd
import numpy as np

df = pd.read_csv("../data/accuracy.csv")

df["approx"] = pd.to_numeric(df["approx"], errors="coerce")
df["value"] = pd.to_numeric(df["value"], errors="coerce")
df["error"] = pd.to_numeric(df["error"], errors="coerce")
df["nodes"] = pd.to_numeric(df["nodes"], errors="coerce")

approx: float = df["approx"]
value: float = df["value"]
nodes: float = df["nodes"]
error: float = df["error"]

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
        x=nodes,
        y=value,
        mode="lines+markers",
        name="Values",
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
        x=nodes,
        y=value,
        mode="lines+markers",
        name="Values",
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

fig3.update_layout(
    title=dict(text="Nodes and Values", font=dict(size=50), automargin=True),
    xaxis=dict(title="Node"),
    yaxis=dict(
        title="Values",
    ),
    font=dict(size=30, color="white"),
    legend=dict(title=dict(text="Type")),
    template="plotly_dark",
    hovermode="x unified"
)

pio.write_image(fig3, "plots/NodeVal.png", scale=3, height=1080, width=1920)