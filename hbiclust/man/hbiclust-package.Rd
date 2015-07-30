\name{hbiclust-package}
\alias{hbiclust-package}
\alias{hbiclust}

\docType{package}

\title{ Hierarchical biclustering }

\description{ Plot a 2D or 3D hierarchical biclustering with respectively, hbiclust.plot and forestogram.}

\details{
TESTING DESCRIPTION.
}

\author{ Alexandre Arsenault }

\references{
~~ Literature or other references for background information ~~
}

\keyword{ package }
\seealso{
% ~~ Optional links to other man pages, e.g. ~~
~~ \code{\link[<pkg>:<pkg>-package]{<pkg>}} ~~
}
\examples{
library(hbiclust)

ranges <- matrix(c(5.0, 7.5,
				   12.0, 20.0,
				   3.0, 15.8,
				   3.0, 30.5,
				   20.0, 21.2,
				   8.0, 12.0,
				   5.0, 16.0,
				   6.0, 9.2,
				   15.0, 20.0,
				   10.0, 11.0), nrow = 10, ncol = 2, byrow = TRUE)

vec = c();

for(i in seq(1, 10))
{
	vec = c(vec, runif(20, ranges[i, 1], ranges[i, 2]));
}

data <- matrix(vec, nrow = 10, ncol = 20, byrow = TRUE)
row_names <- seq(1, 10, 1);
col_names <- seq(1, 20, 1);
dimnames(data) <- list(row_names, col_names)

# Calculate hierarchical biclustering.
v <- hbiclust(data);

# Draw forestogram.
forestogram(v, cut_height = 11.0, 
			line_width = 3.0, 
			interpolate_tree_colors = FALSE, 
			# cut_base_contour_width = 2, 
			cut_base_alpha = 0.4,
			draw_only_from_cut = TRUE);

# Draw two dimension dendrogram.
hbiclust.plot(v, cut_height = 11);
}
