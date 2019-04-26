#
# Cozmonaut
# Copyright 2019 The Cozmonaut Contributors
#

from cozmonaut.op import Op


class OpInteract(Op):
    """
    The interactive mode operation.
    """

    def main(self):
        print('interact')
        return 0
