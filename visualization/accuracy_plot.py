import plotly.graph_objects as go
import plotly.io as pio
import pandas as pd

df = pd.read_csv("../data/accuracy.csv")

approx: float = df["approx"]
value: float = df["value"]
nodes: int = df["nodes"]
error: float = df["error"]

fig = go.Figure()

fig.add_trace(
    go.Scatter(
        x=nodes,
        y=error,
        mode="lines+markers",
        name="Error %",
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
    yaxis=dict(title="Error %"),
    font=dict(size=30),
    yaxis_type="log",
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
    yaxis=dict(title="Values & Approximations"),
    font=dict(size=30, color="green"),
    yaxis_type="log",
    legend=dict(title=dict(text="Type")),
    template="plotly_dark",
    hovermode="x unified"
)

pio.write_image(fig2, "plots/ValVsApprox.png", scale=3, height=1080, width=1920)