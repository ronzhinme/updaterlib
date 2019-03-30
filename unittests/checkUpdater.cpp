
#include "../src/updater.h"

bool isOnCheckResultCorrect = false;

void onCheckResult(OperationType o, Result r, const ExtraInfo & i)
{
    printf("%s [%d] [%d]\n", __FUNCTION__, o, r);
    isOnCheckResultCorrect = (o == TYPE_CHECK && r == RESULT_SUCCESS);
}

int main()
{
    Updater updater;
    updater.onOperationResultEvent([](OperationType o, Result r, const ExtraInfo & i){onCheckResult(o,r,i);});
    updater.checkForUpdate();

    return isOnCheckResultCorrect ? EXIT_SUCCESS : EXIT_FAILURE;
}