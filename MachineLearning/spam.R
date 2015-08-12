##################################
 # spam.R
 # Brief: spam prediction code
 # Auther: nowerzt@gmail.com
##################################
 library(kernlab) #use its spam data
 library(caret) #algo lib
 
 # define the training set, testing set
 training <- NULL
 testing <- NULL
 
 getData <- function() {
 	data(spam) # load the spam data
 	# 60% training
 	inTraining <- createDataPartition(y=spam$type,
 					p=.6, list=FALSE)
 	training <<- spam[inTraining,]
 	testing <<- spam[-inTraining,]
 }
 
 spam_main <- function() {
 	# main process 
 	getData()
 	# choose generalized linear model
 	modelFit <- train(type~., data=training, method="glm")
 	# predict
 	predictions <- predict(modelFit, newdata=testing);
 	# show validation
 	confusionMatrix(predictions, testing$type)
 }
 