#
# Cozmonaut
# Copyright 2019 The Cozmonaut Contributors
#

from cozmonaut.op import Op


class OpFriendRemove(Op):
    """
    The friend remove operation.
    """

    def main(self):
        print('friend remove')
        return 0
