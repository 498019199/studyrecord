#1. 两数之和
class Solution:
    def twoSum1(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        count = len(nums)
        for i in range(count):
            for j in range(i + 1, count):
                if target == nums[i] + nums[j]:
                    return [i, j]
        return []

    # 方法二：哈希表
    def twoSum2(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        rets = {}
        for i in range(len(nums)):
            value = nums[i]
            f = target - value
            if None != rets.get(f):
                return [rets.get(f), i]
            rets[value] = i
        return []

    # 13. 罗马数字转整数    
    # 若存在小的数字在大的数字的左边的情况，根据规则需要减去小的数字。对于这种情况，
    # 我们也可以将每个字符视作一个单独的值，若一个数字右侧的数字比它大，则将该数字的符号取反。
    # 列如 XIV 可视作 X-I+V=10-1+5
    def romanToInt(self, s: str) -> int:
        loma = {"I":1,"V":5,"X":10,"L":50,"C":100,"D":500,"M":1000,}
        total = 0
        for i, ch in enumerate(s):
            curValue = loma[ch]
            if i < len(s) -1 and curValue < loma[s[i + 1]]:
                total -= curValue
            else:
                total += curValue
        return total

    # 1125. 最小的必要团队
    def smallestSufficientTeam(self, req_skills: list[str], people: list[list[str]]) -> list[int]:
        return []
    
    # 2427. 公因子的数目
    def commonFactors(self, a: int, b: int) -> int:
        count = 0
        for i in range(1, min(a, b) + 1):
            if (0 == a % i and 0 == b % i):
                count+=1       
        return count


solution = Solution()
ret = solution.smallestSufficientTeam(["java","nodejs","reactjs"], [["java"],["nodejs"],["nodejs","reactjs"]])
