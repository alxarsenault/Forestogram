dyn.load("my_func.so")

power <- function(x) 
{
	if (!is.numeric(x))
	{
	   stop("argument x must be numeric")
	}	

	out <- .C("power", x = as.double(x))
	return(out$x)
}	

cube <- function(x) 
{
	if (!is.numeric(x))
	{
	   stop("argument x must be numeric")
	}	

	out <- .C("cube", x = as.double(x))
	return(out$x)
}	

mytest <- function(x) 
{
	# if (!is.numeric(x))
	# {
	#    stop("argument x must be numeric")
	# }	

	out <- .C("mytest", x = x, n = length(x))
	
	return(out$x)
}	
