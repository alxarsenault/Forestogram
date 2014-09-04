xlims = range(trees[,1])
ylims = range(trees[,2])
zlims = range(trees[,3])

bot = min(zlims[1]) - diff(zlims)/20

rgl.quads(xlims[c(1,2,2,1)],
          rep(bot, 4),
          ylims[c(1,1,2,2)],
          col = "gray")

for(i in 1:nrow(trees)) {
  rgl.lines(rep(trees[i,1],2),
            c(trees[i,3], bot),
            rep(trees[i,2], 2),
            color = "white")
}
# set.seed(314)
# x <- rnorm(1000)
# y <- rnorm(1000)
# z <- rnorm(1000)

# x <- seq(-1, 1, by=0.1)
# y <- seq(-1, 1, by=0.1)
# z <- seq(-1, 1, by=0.1)

#x <- 1:10
#y <- 1:10
#z <- matrix(outer(x-5,y-5) + rnorm(100), 10, 10)
#z <- 1:10

#open3d()
#open3d(windowRect = c(00,00, 600, 600) )
#planes3d(0, 0, 1, 0, alpha=1.0, col="blue")

#persp3d(x, y, z, col="red", alpha=0.7, aspect=c(1,1,0.5))
#persp3d(x, y, z, col="red", alpha=0.7, aspect=c(1,1,0.5))

#grid3d(c("x", "y+", "z"))
 
# open3d(windowRect = c(00,00, 1000, 5760) )
# #lines(0, 10, 10)
# #plot3d(x, y, z)#cex=1.5, size=4, type="s", col=rainbow(1000) )

# grid3d(x, y, z, at = NULL, col = "gray", lwd = 1, lty = 1, n = 5)

# planes3d(0, 0, 1, 0, alpha=1.0, col="blue")
# planes3d(0, 0, 0.8, -1, alpha=0.5)

#ersp3d(x=seq(0,10), y=seq(0,10), z=1)


# ii <- shade3d(translate3d(cube3d(), 1, 1, 1), col="blue", alpha = 1)
# shade3d(translate3d(cube3d(), 1, 1, 1), col="white", alpha = 0.5)
# rgl.pop(id = ii)