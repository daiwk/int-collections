TreeNode findAncestor(TreeNode root, TreeNode node1, TreeNode node2) {
    if (root == null) return null;
    if (root == node1 || root == node2) return root;
    TreeNode left  = findAncestor(root.left,  node1, node2);
    TreeNode right = findAncestor(root.right, node1, node2);
    if (left != null && right != null) return root;
    return right == null ? left : right;
}
