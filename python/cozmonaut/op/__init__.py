#
# Cozmonaut
# Copyright 2019 The Cozmonaut Contributors
#

from abc import ABC, abstractmethod


class Op(ABC):
    """
    An operation.
    """

    @abstractmethod
    def main(self) -> int:
        """
        The main method of the operation.
        :return: The exit code (zero for success)
        """
        raise NotImplementedError
